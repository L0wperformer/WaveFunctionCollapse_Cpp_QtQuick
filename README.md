# WaveFunctionCollapse_Qt_Qml
Welcome to my implementation of the WFC-algorithm in the Qt Framwork.    
An explanation (and cooler implementations) of the algorithm can be found on following sources:  
  
[Superpositions, Sudoku, the Wave Function Collapse algorithm.](https://youtu.be/2SuvO4Gi7uY) by Martin Donald  
[Coding Challenge 171: Wave Function Collapse](https://youtu.be/rI_y2GAlQFM) by @[CodingTrain](https://github.com/CodingTrain/Wave-Function-Collapse)  

I thought this is a fun algorithm to implement.  
There's still some work to do and I have some ideas in mind that I will implement at some point.  
Features until now: 
- Customizable dimensions (but only square for now)  
- Customizable weights  
- Customizable sockets  
- Customizable amount of sockets if you choose to make your own tiles
- If you dont want to make your own Tiles in qml you may use "Tile.qml" to add e.g. Tiles in .png. Just keep in mind you have to change the `onDrawTile` and/or   the `onGridInit` signal handlers in `Canvas.qml`. Contact me if you don't get it working ;). Or look at older versions of the project.
- Clicking changes the colors to "nightmode" and back easily, even while running. Qml can be very cool.

In this example a weightlist is active that discourages Tiles that connect diagonals to horizontals, resulting in clusters:  

![neueGif](https://user-images.githubusercontent.com/91269094/195852982-0b7a0e67-6e20-4728-a408-97903dcc92cb.gif)

Here, all times are equally as likely. Also the colors get switched.  

![neueGifDarkmode](https://user-images.githubusercontent.com/91269094/195854808-5ca810c9-84cc-413c-9283-e5c0acf74e66.gif)

The limit where you actually see someting is around 100x100. Here is a Video of that being solved:  
For better Quality Click on GIF or [here](https://youtu.be/J-63SCiYXXs)
![](https://user-images.githubusercontent.com/91269094/196060171-a749b2c3-bf01-4dbb-a9b6-8137c69cbbc0.gif)

The old QML implementation was so slow that this took over an hour. Click [here](https://youtu.be/iqUwF_EtlBcy) for a timelapse of that
