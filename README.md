# branching_test_thing
small windows c program for testing branching/non-branching

times from my 9950x3d:

  clang -march=x86-64-v4 -O0:    clang -march=x86-64-v4 -O3:
                                              
    sorted branching:              sorted branching:
      100k iters: 1.939              100k iters: 0.536
        1M iters: 18.791               1M iters: 5.217
                                             
    sorted branchless:             sorted branchless:
      100k iters: 2.621              100k iters: 0.217
        1M iters: 26.044               1M iters: 1.994
                                             
    unsorted branching:            unsorted branching:
      100k iters: 5.006              100k iters: 1.857
        1M iters: 49.526               1M iters: 16.241
                                           
    unsorted branchless:           unsorted branchless:
      100k iters: 2.696              100k iters: 0.206
        1M iters: 28.847               1M iters: 1.937
                                   
                                   
                        conclusion:    
                    vectorization rocks         
