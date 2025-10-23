# Game of Life — C++ & OpenGL

A little project to keep learning modern OpenGL and C++, while experimenting with an interactive and visually dynamic simulation: a custom version of Conway’s Game of Life.

The goal was not only to reproduce the cellular automaton, but also to experiment with parallelization, GPU data streaming, and real-time rendering optimization.

## Features
	•	Custom Game of Life ruleset
			Includes extended behaviors such as mutation types (creator, killer, long-life) and smooth cell lifetime/age tracking.
	•	Multithreaded simulation
			The physics (cell updates) run on a dedicated thread, completely independent from the rendering thread.
	•	OpenGL dynamic rendering
			Uses VBO streaming (glBufferSubData) to send millions of vertices per frame efficiently to the GPU.
	•	Parallel CPU generation
			The cell-to-vertex conversion is done using OpenMP for massive grids (up to 2000×2000).
	•	Color gradient based on age
			Older cells glow with warmer tones, while newly born ones appear colder — offering a sense of temporal evolution.

## Result
	
You can find dome cool pictures in './result-image' where you can see paterns or giant structures. 
