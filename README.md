# Project #6 fractol, Dec 2014
>>>>> #####Fractal exploration project.

#####Grade ``(TBD/100)`` ``(TBD/1..)*``
--------  -----------------------
Goals:
- [X] Use "minilibX", school's truncated version of "X11".
- [X] Read arguments to choose wich fractal to show.
- [X] Mandelbrot set. Zoom with mouse scroll.
- [X] Julia sets. Zoom with mouse scroll. Mouse position defines wich Julia to show.
- [X] One more fractal. Zoom with mouse scroll.

Recommended bonuses:
- [X] Movements.
- [X] Change colors on key press.
- [ ] More fractals.
- [ ] 3d representation.
- [ ] Open two frames for two fractals, at the same time.

My additions:
* [X] Sierpinsky carpet, as a third fractal.
- [X] "+/-" keys to change the number of loops.
- [X] Time dependant movements, instead of CPU dependant. ([events.c](https://github.com/Ngoguey42/proj06_graph_fractol/blob/master/events.c)) ([libft/srcs/ft_clock[...].c](https://github.com/Ngoguey42/proj06_graph_fractol/tree/master/libft/srcs))
- [X] Multi thread rendering. ([draw_screen_async.c](/draw_screen_async.c))
- [ ] CUDA rendering. (failed at compilation) ([draw_mandelbrot_cuda.cu](/draw_mandelbrot_cuda.cu))
- [X] SDL compatibility. (dirty)

Usage:
```sh
make
./fractol JMS
```
![Mandelbrot](http://i.imgur.com/xRBaaFC.png)
<br><br><br><br><br><br><br><br>


```
All my C files strictly observes school's norm, it may often lead to odd or illogical syntaxes.
- [ ] Forbiden keywords: for, do, switch, goto.
- [ ] No more than 25 lines inside a function block.
- [ ] No more than 80 characters per lines.
- [ ] At most 5 functions per files.
- [ ] Only 1 declaration per line.  
- [ ] No declaration and assignation on the same line.
- [ ] At most 1 assignation per line.
- [ ] No more than 4 parameters for a function.
- [ ] No nested ternary.
- [ ] Comments alowed at the top of the file.
```
```
*
- A grade of 85 was required to validate the project.
- A maximum grade of 1.. was reachable.
- Second sessions are organised for failed projects.
```
