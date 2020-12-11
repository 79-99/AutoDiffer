This directory holds examples of usage. The directory structure is outlined below. 
Each subdirectory has a Make file. Examples can be built by running `make` followed
by the name of the example. For example: `./example_ad_node_scalar`.

```
|---examples
|   |---example_adnode_scalar.cpp            // Simple usage of ADNode and Value objects to derive scalar function.
    |---example_autodiffer_jacobian.cpp      // Demonstration of how to get jacobian of 3 vector functions each with 2 variables.
    |---example_autodiffer_scalar.cpp        // Simple usage of AutoDiffer on scalar function.
    |---example_autodiffer_scalar2.cpp       // More complicated scalar function with AutoDiffer.
    |---example_autodiffer_vector.cpp        // Vector function with AutoDiffer.
    |---Makefile
    |---live_demo
    |   |---example_live_demo.cpp            // Basic example used for live demo in video.
        |---Makefile
    |---multithreading
    |   |---example_multiple_functions.cpp   // Simplest multi-threaded example using std::threads to show performance improvements.
        |---Makefile
        |---benchmark
        |   |---benchmark.sh                 // Shell script to run many openmp and std thread examples. writes to data/.
            |---example_opennmp.cpp          // Openmp multithreaded example. User specifies number of threads, equations, and operations.
            |---example_std_thread.cpp       // Same as above but with std::thread.
            |---Makefile
            |---data
            |   |---openmp_case_A.txt        // Case A data for Openmp created by benchmark.sh.
                |---openmp_case_B.txt        // Case B data for Openmp created by benchmark.sh.
                |---std_case_A.txt           // Case A data for std::thread created by benchmark.sh.
                |---std_case_B.txt           // Case B data for std::thread created by benchmark.sh.
                |---data.ipynb               // Jupyter notebook to plot data.
                |---caseA_openmp.png         // Plot of results for Case A, openmp.
                |---caseB_openmp.png         // Plot of results for Case B, openmp.
                |---caseA_std.png            // Plot of results for Case A, std::thread.
                |---caseA_std.png            // Plot of results for Case B, std::thread.
```  

## Base examples.

Each of these examples live in the top level `examples/` directory. Running `make`
in this directory will build all five of the following tests. Each can be ran with
their respective name after make finishes (e.g., `./example_autodiffer_jacobian`).
Each of these examples prints to the terminal the expected and AutoDiffer results.
Examples 1,3,4 are one scalar valued function. Example 2 is 3 functions of 2 variables.
Example 5 is one function of 2 variables.

1. `example_adnode_scalar.cpp`
2. `example_autodiffer_jacobian.cpp`
3. `example_autodiffer_scalar.cpp`
4. `example_autodiffer_scalar2.cpp`
5. `example_autodiffer_vector.cpp` 

## Multithreading examples.

### Base example.
Based on our multithreading extension, we present a number of further examples. The first is
`multithreading/example_multiple_functions.cpp`. This demonstrates the simplest multithreading
use case which is passing a vector of functions into the `DeriveStdThread` call. This example 
can be built by running `make` in `examples/multithreading`, and is run with 
`./example_multiple_functions`, which should provide an output similar to the one below:

```
Multithreaded time (microseconds): 4308
Single threaded time (microseconds): 16392
```

### Benchmark examples.
In the `examples/multithreading/benchmark/` directory, there are two more examples:

1. `example_openmp.cpp`
2. `example_std_thread.cpp`

which demonstrate the OpenMp and std::thread implementations of multithreading respectively.
These can be built by running `make` in `examples/multithreading/benchmark/`. 
Following the make, we recommend running `bash benchmark.sh` to collect data for your machine.
This will test a number of combinations of many equations and many ops per equation for both
openmp and std::thread. Noe that you will need OpenMp installed in order to run the 
benchmarking. The compiler flags will take care of the rest. The output from the benchmarking script
should look like:

```
Collecting data for std::thread Case A .................... done!
Collecting data for std::thread Case B ..................... done!
Collecting data for openmp Case A .................... done!
Collecting data for openmp Case B ..................... done!
Data written to data/ directory!
```

Data is written to data/ and in the jupyter notebook [data.ipynb](multithreading/benchmark/data/data.ipynb) has
functions to plot the data that was generated. 

We collect data for two broad cases:
1. Case A: Large equations (in number of ops), but relatively few of them.
2. Case B: Small equations, but many of them.

Specifically we collect the following data:
1. Case A: Runtime for i in range 1, 2, ..., 20 equations, where each equation has 1500 operations.
1. Case B: Runtime for i in range 1, 1000, 2000, ..., 20000 equations, where each equation has 5 operations.

We collect this data for std::thread (which spins up a new thread for each equation) and
for openmp (which we default to six threads). We observe the following tradeoff between the 
multithreading options:

#### std::thread
1. Pros:
- Runtimes are consistently about 4x faster that single threaded version when there are relatively
few functions (Case A). 
- Outperforms openmp when there are few equations that each have a ton of operations (Case A).
- Also has the benefit of not needing a special compiler to run.
- Runtimes appear to be more consistent.

2. Cons:
- In the case where there are many functions, but each function is relatively small (Case B),
std::threads suffer. This is because a new thread is created for each function and
as a result the thread creation overhead overwhelms the performance improvement.

This is represented in the following images.

![std_caseA](multithreading/benchmark/data/caseA_std.png)

On the left plot we see the timings for single and multithreaded versions of the 
derivation. The right plot shows the ratio of single / multi, which can be 
interpreted as the speedup provided from the multithreading.
We see that for case A, std::thread has very consistent performance at about 4x. This was run
on a 1.4 GHz Quad-Core Intel Core i5, so 4x is expected.

![std_caseB](multithreading/benchmark/data/caseB_std.png)

We see that for case B, the std thread implementation is actually doing *worse* 
than the single threaded version (emphasized by the right plot approaching 0). The 
reason it does worse is because the overhead of spinning up so many threads overwhelms 
the performance improvement from the parallelization.  

#### openmp
1. Pros:
- Sees improvement for both Case A (about 3x) and Case B (about 4x). 
- Outperforms std::thread when there are many equations that each have a few of operations (Case B).

2. Cons:
- Requires a special compilation phase and adds an additional external dependency.

This is represented in the following images.

![std_caseA](multithreading/benchmark/data/caseA_openmp.png)

For case A, we see that openmp is performing about 3x as well as single threaded. However there
is a lot of variance in the exact ratio.

![std_caseB](multithreading/benchmark/data/caseB_openmp.png)

We see that for case B, the openmp version is outperforming the single thread 
by a consistent 4x. Again this makes sense given the hardware it was run on. The performance
here is so much better than std thread because the openmp version reuses threads 
by maintaining thread pools that handle each iteration of the loop. Thus there is no
growth in the thread creation overhead, and openmp can max out the hardware. 

#### Conclusion.
Based on this analysis, we recommend the following for users who wish to use
multithreaded AutoDiffer. 

1. If the user can get openmp, then they should probably use this. Openmp
provides the most consistent results for improvement across case A and case B (even 
though std thread performs marginally better in case A). This is the safest way to
get a certain performance boost.

2. If the user cannot access openmp, then they should consider the equations that they are
running on. If their set of equations seems closer to Case A, then they should use 
std thread AutoDiffer to see improvement. If their set of equations seems closer to 
Case B, then we encourage them to instead use the single threaded version of 
the AutoDiffer. 

-----

You can running these examples without calling the benchmarking script if you would like.
Both require command line arguments.

1. `./example_openmp num_equations num_ops num_threads`
- num_equations represents how many equations to create.
- num_ops represents how many ops per equation.
- num_threads set the open_mp number of threads used.
- `./example_openmp 100 100 5`
2. `example_std_thread.cpp`
- num_equations represents how many equations to create.
- num_ops represents how many ops per equation.
- `./example_std_thread 100 100`


See [Documentation](https://github.com/79-99/cs107-FinalProject/blob/master/docs/documentation.ipynb).
