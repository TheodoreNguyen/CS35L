Theodore Nguyen
704-156-701

CS35L week 9 homework: Multithreaded performance

For most of it, I basically just parallelized alot of the existing code. I
sectioned off the image into columns as we wanted to split the image into
columns for each thread. I moved some variables to global if it was used in
both the main and the function call, as well as most of the code to the
function called threadingfcn. 

Each thread works on its own part of the image separately; the pthread_join
function will join them together to produce the image once all the threads
finish. 

The multithreading speeds up the program by about double when using two
threads, and quadruple when using eight threads.

