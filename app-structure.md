creativeThinking
================

Attract Loop
	Graphic Loop

Instructions
	Text / Audio playback

CameraHandler
	load
	display video
	Take picture
	pass photo onto imagehandler

ImageHandler
	display image
	process image
	save image
	gallery view

BrainHandler
	initiate / setup mindwave
	record raw brain data
	process usable data
	pass on brain data

Effect Handler
	Turn on and off effects
	handle effect parameters
	create process pipeline
	take in image
	render out and pass back image
	debug display steps

Effects
=======
	Gaussian Blur
	Sketch
		FindEdge
		Invert
		Blend Subtract
	WaterColor
		Paper Texture
		Fluid Simulation
		Particle Divergence and Relaxation

FX Pipe
=======
Image In => \ 	=> findEdges - - - - - - - - - - - - - - -- - - - - - - -> / => Sketch [subtract] edges = Stencil Image
					   \  => GreyScale - - - - - - > / => gBlurInverted / GreyScale /
						  \ => GaussianBlur => Invert /


