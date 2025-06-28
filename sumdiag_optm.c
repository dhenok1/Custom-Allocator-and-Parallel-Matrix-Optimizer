// optimized versions of matrix diagonal summing
#include "sumdiag.h"

////////////////////////////////////////////////////////////////////////////////
// REQUIRED: Paste a copy of your sumdiag_benchmark from an ODD grace
// node below.
//
// -------REPLACE WITH YOUR RUN + TABLE --------
// 
// ==== Matrix Diagonal Sum Benchmark Version 5 ====
// ------ Tuned for ODD grace.umd.edu machines -----
// Running with 5 sizes (max 8192) and 4 thread_counts (max 4)
//   SIZE   BASE #T   OPTM  SPDUP POINTS
//   1024  0.027  1  0.014   1.99   0.23 
//                2  0.007   3.83   0.44
//                3  0.005   5.35   0.55
//                4  0.007   3.73   0.43
//   1101  0.031  1  0.016   1.94   0.23 
//                2  0.008   3.71   0.46
//                3  0.006   5.11   0.58 
//                4  0.008   3.80   0.47 
//   2048  0.186  1  0.052   3.58   0.84 
//                2  0.026   7.06   1.28
//                3  0.019   9.80   1.50 
//                4  0.021   8.66   1.42 
//   4099  1.215  1  0.212   5.73   2.29 
//                2  0.108  11.25   3.18 
//                3  0.075  16.23   3.66 
//                4  0.071  17.13   3.73 
//   8192  7.254  1  0.858   8.45   5.61 
//                2  0.428  16.95   7.43 
//                3  0.292  24.83   8.44 
//                4  0.233  31.11   9.03 
// RAW POINTS: 51.80
//  _   _                 _   _           _   _       _____ _    ____ _____ _
// | \ | | _____      __ | |_| |__   __ _| |_( )___  |  ___/ \  / ___|_   _| |
// |  \| |/ _ \ \ /\ / / | __| '_ \ / _` | __|// __| | |_ / _ \ \___ \ | | | |
// | |\  | (_) \ V  V /  | |_| | | | (_| | |_  \__ \ |  _/ ___ \ ___) || | |_|
// |_| \_|\___/ \_/\_/    \__|_| |_|\__,_|\__| |___/ |_|/_/   \_\____/ |_| (_)

//                              ...,?77??!~~~~!???77?<~....
//                         ..?7`                           `7!..
//                     .,=`          ..~7^`   I                  ?1.
//        ........  ..^            ?`  ..?7!1 .               ...??7
//       .        .7`        .,777.. .I.    . .!          .,7!
//       ..     .?         .^      .l   ?i. . .`       .,^
//        b    .!        .= .?7???7~.     .>r .      .=
//        .,.?4         , .^         1        `     4...
//         J   ^         ,            5       `         ?<.
//        .%.7;         .`     .,     .;                   .=.
//        .+^ .,       .%      MML     F       .,             ?,
//         P   ,,      J      .MMN     F        6               4.
//         l    d,    ,       .MMM!   .t        ..               ,,
//         ,    JMa..`         MMM`   .         .!                .;
//          r   .M#            .M#   .%  .      .~                 .,
//        dMMMNJ..!                 .P7!  .>    .         .         ,,
//        .WMMMMMm  ?^..       ..,?! ..    ..   ,  Z7`        `?^..  ,,
//           ?THB3       ?77?!        .Yr  .   .!   ?,              ?^C
//             ?,                   .,^.` .%  .^      5.
//               7,          .....?7     .^  ,`        ?.
//                 `<.                 .= .`'           1
//                 ....dn... ... ...,7..J=!7,           .,
//              ..=     G.,7  ..,o..  .?    J.           F
//            .J.  .^ ,,,t  ,^        ?^.  .^  `?~.      F
//           r %J. $    5r J             ,r.1      .=.  .%
//           r .77=?4.    ``,     l ., 1  .. <.       4.,
//           .$..    .X..   .n..  ., J. r .`  J.       `'
//         .?`  .5        `` .%   .% .' L.'    t
//         ,. ..1JL          .,   J .$.?`      .
//                 1.          .=` ` .J7??7<.. .;
//                  JS..    ..^      L        7.:
//                    `> ..       J.  4.
//                     +   r `t   r ~=..G.
//                     =   $  ,.  J
//                     2   r   t  .;
//               .,7!  r   t`7~..  j..
//               j   7~L...$=.?7r   r ;?1.
//                8.      .=    j ..,^   ..
//               r        G              .
//             .,7,        j,           .>=.
//          .J??,  `T....... %             ..
//       ..^     <.  ~.    ,.             .D
//     .?`        1   L     .7.........?Ti..l
//    ,`           L  .    .%    .`!       `j,
//  .^             .  ..   .`   .^  .?7!?7+. 1
// .`              .  .`..`7.  .^  ,`      .i.;
// .7<..........~<<3?7!`    4. r  `          G%
//                           J.` .!           %
//                             JiJ           .`
//                               .1.         J
//                                  ?1.     .'
//                                      7<..%

//        _  ___    ____                        _ _
//    _  / |/ _ \  | __ )  ___  _ __  _   _ ___| | |
//  _| |_| | | | | |  _ \ / _ \| '_ \| | | / __| | |
// |_   _| | |_| | | |_) | (_) | | | | |_| \__ \_|_|
//   |_| |_|\___/  |____/ \___/|_| |_|\__,_|___(_|_)
// |
// TOTAL POINTS: 40 / 30
// -------REPLACE WITH YOUR RUN + TABLE --------


//Diagonal index formula  index = (col_size-1)




// You can write several different versions of your optimized function
// in this file and call one of them in the last function.
typedef struct {
  int thread_id;                // logical id of thread, 0,1,2,...
  int thread_count;             // total threads working on summing
  matrix_t mat;                 // matrix to sum
  vector_t vec;                 // vector to place sums
  pthread_mutex_t *vec_lock;    // mutex to lock the vec before adding on results
} colsums_context_t;

void *sumdiag_Worker1(void *args){
  // extract the parameters / "context" via a caste
  colsums_context_t ctx = *((colsums_context_t *) args);

  // extract the matrix and vector for the parameter context struct
  matrix_t mat = ctx.mat;
  vector_t vec = ctx.vec;
  //Get index bounds
  int col_start = 0;
  int col_end = mat.cols;

  int rows_per_thread = mat.rows / ctx.thread_count;
  int row_start = ctx.thread_id * rows_per_thread;
  int row_end = (ctx.thread_id+1) * rows_per_thread;
  if(ctx.thread_id==ctx.thread_count-1){
    row_end = mat.rows;
  }

  int *local_vec = malloc(sizeof(int) * vec.len);
  for(int i=0; i<vec.len; i++){
    local_vec[i] = 0;
  }

  // iterate over the matrix adding column elements to the local sum
  for(int i=row_start; i<row_end; i++){
    for(int j=col_start; j<col_end; j++){
      local_vec[mat.cols-i+j-1] += MGET(mat, i, j);
    }
  }

  pthread_mutex_lock(ctx.vec_lock);

  // TODO: Add on the local results to the shared vec in a loop
  for(int i=0; i < vec.len; i++){
    vec.data[i] += local_vec[i];
  }

  // TODO: Unlock the mutex
  pthread_mutex_unlock(ctx.vec_lock);

  // free the local vector before ending
  free(local_vec);
  return NULL;

}

int sumdiag_VER1(matrix_t mat, vector_t vec, int thread_count) {
  // initialize the shared results vector
  for(int j=0; j<vec.len; j++){
    VSET(vec,j,0);
  }

  // init a mutex to be used for threads to add on their local results
  pthread_mutex_t vec_lock;
  pthread_mutex_init(&vec_lock, NULL);


  pthread_t threads[thread_count];           // track each thread
  colsums_context_t ctxs[thread_count];      // context for each trhead

  // loop to create threads
  for(int i=0; i<thread_count; i++){

    // TODO: fill field values for the context to pass to threads;
    // thread IDs are 0,1,2,... and are used to determine which part
    // of the matrix to operate on. The remaining data are copies of
    // local data that enable the thread to "see" the matrix and
    // vector as well as utilize the mutex for coordination.

    ctxs[i].thread_id = i;
    ctxs[i].thread_count = thread_count;
    ctxs[i].mat = mat;
    ctxs[i].vec = vec;
    ctxs[i].vec_lock = &vec_lock;
    // Loop to create the threads
    pthread_create(&threads[i], NULL,        // start worker thread to compute part of answer
                   sumdiag_Worker1,
                   &ctxs[i]);
  }
  
  // TODO: use a loop to join the threads
  for(int i=0; i<thread_count; i++){
    pthread_join(threads[i], (void**) NULL);
  }
  
  pthread_mutex_destroy(&vec_lock);          // get rid of the lock to avoid a memory leak
  return 0;
}

int sumdiag_VER2(matrix_t mat, vector_t vec, int thread_count) {
  // OPTIMIZED CODE HERE
  return sumdiag_VER1(mat, vec, thread_count);
}

int sumdiag_OPTM(matrix_t mat, vector_t vec, int thread_count) {
  // call your preferred version of the function
  return sumdiag_VER1(mat, vec, thread_count);
}

////////////////////////////////////////////////////////////////////////////////
// REQUIRED: DON'T FORGET TO PASTE YOUR TIMING RESULTS FOR
// sumdiag_benchmark FROM AN ODD GRACE NODE AT THE TOP OF THIS FILE
////////////////////////////////////////////////////////////////////////////////
