/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandelbrot_cuda.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 15:58:47 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/11 17:31:48 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <fractol.h> */

typedef unsigned char t_byte;

typedef union   u_co
{
    struct
    {
        t_byte  b;
        t_byte  g;
        t_byte  r;
        t_byte  a;
    }           s;
    int         i;
}               t_co;

typedef struct  s_cooi
{
    int         x;
    int         y;
    int         z;
}               t_cooi;

typedef struct  s_coof
{
    float       x;
    float       y;
    float       z;
}               t_coof;

typedef struct  s_img
{
    void        *img;
    char        *dat;
    int         bpp;
    int         lsz;
    int         end;
    int         totby;
}               t_img;

typedef struct  s_juli
{
    t_coof      m_coo;
    t_coof      curc;
}               t_juli;

typedef struct  s_mand
{

    int         idk;

}               t_mand;

typedef struct  s_fra
{
    void        *serv;
    void        *win1;
    t_img       s;
    int         ev[11];
    t_coof      coo;
    float       zoom;
    t_coof      scdt;
    t_coof      pxin;
    t_cooi      m_cooscr;
    int         type;
    t_juli      j;
    t_mand      m;
    int         part;
}               t_fra;

# define ABS(x) ((x) < 0 ? -(x) : (x))

# define VCOTOI(R, G, B, A) ((t_co){{B, G, R, A}})

# define WINY (float)652.

# define WIN_Y (int)(WINY)
# define WIN_X (int)(WINY * (float)1.0)

/* #include <string.h> */
/* #include <stdlib.h> */

/* #define LOL (80 * fra.zoom)  */
/* #define LOL2 (0.01 / fra.zoom) */
#define LOL (80 * 2.) 
#define LOL2 (0.01)

__device__ int fra_puts_dst_cuda(t_fra fra, int dst, t_co c, char *d_dat)
{
    int             i;

    i = -1;
    while (++i < (fra.s.bpp / 8))
    {
        d_dat[dst + i] = (char)c.s.b;
        c.i >>= 8 ;
    }
    return (0);

}


/* int		julia_zero_escape_val(t_fra fra, t_coof pix) */
__device__ int		julia_zero_escape_val(t_coof d_pix)
{
	t_coof	zero;
	t_coof	tmp;
	int		i;

/* 	ft_bzero(&zero, sizeof(t_coof)); */
	zero.x = 0;
	zero.y = 0;
	i = 0;
	while (i < LOL)
	{
		i++;
		tmp = zero;
		zero.y = 2 * tmp.x * tmp.y + d_pix.y;
		zero.x = tmp.x * tmp.x - tmp.y * tmp.y + d_pix.x;
		if (zero.x > 100. || zero.y > 100.)
			break;

		if (ABS(tmp.x - zero.x) < LOL2 && ABS(tmp.y - zero.y) < LOL2)
			return (LOL);
	}
	return (i);
}

/* void	fra_draw_mandelbrot2(t_fra fra) */
__global__ void	fra_draw_mandelbrot2(t_fra d_fra, char *d_dat)
{
	t_coof		pix;
	int			i;
	int			j;
	int			c;

	c = threadIdx.x;
	pix = d_fra.coo;
	i = -1 + (c - 1) * WIN_X;
	while (i < (c * WIN_X - 1))
	{
		i++;
		if (i % WIN_X == 0)
		{
			pix = d_fra.coo;
			pix.y += (float)(i / WIN_X) * d_fra.pxin.y;
		}
		else
			pix.x += d_fra.pxin.x;
		j = julia_zero_escape_val(pix);
		if (j < LOL)
			fra_puts_dst_cuda(d_fra, i * 4, VCOTOI(255, 0, 0, 0), d_dat);
		else
			fra_puts_dst_cuda(d_fra, i * 4, VCOTOI(0, 255, 0, 0), d_dat);
		
	}
}

int		fra_draw_mandelbrot(t_fra fra)
{
	t_fra		*d_fra;
/* 	char		d_dat[WIN_X * WIN_Y * 4]; */
	char		*d_dat;

	cudaMalloc((void**)&d_fra, sizeof(t_fra));
	cudaMalloc((void**)&d_dat, WIN_X * WIN_Y * sizeof(int));
	
	cudaMemcpy(d_fra, &fra, sizeof(t_fra), cudaMemcpyHostToDevice);

	fra_draw_mandelbrot2<<< 1, WIN_Y >>>(*d_fra, d_dat);


	return (0);
}
