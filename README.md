## Dining Philosphers

diningFilo.c implements the solution to the dining philosphers problem using semaphores and simple ordering to avoid the theoretical deadlock.
All but the  fifth philospher have the 

### Modified Dinging Philospher

 diningFilo_mod.c solves a modification of the dining philosphers problem, which apart from
 the the 5 forks also includes two sauce bowls which also needs to be procured
 for the philosphers to eat. This was easily solved using the fact that
 at a time only 2 philosphers would be eating given the problem statement
 hence the sauce bowls shouldn't restrict the philosphers. An if condtion
 checks the availbility of the bowls and assigns to the philosphers. Philospher
 reliquish the bowls along with the forks.


### Solution without synchronization primitives

dininFilo2.c and diningFilo_mod2.c implement the solution to the same problem statement
except this time no synchronization primitves. only 2 threads act at a time
each thread contains non conflicting philosphers, and sending the philosphers into the 
thread in a strict order is done outside the the threads


## Acknowledgements

 - [Lecture 6 (Sambuddho Chakravarty)](https://drive.google.com/file/d/1OebnYv8jMEdVTr3OkL8irGsG8ROEIKJz/view)
 - [Jacob Sorber - semaphores](https://www.youtube.com/watch?v=ukM_zzrIeXs&t=365s)
 - [Gate Smashers - Dining Philospher](https://www.youtube.com/watch?v=HHoB2t_B6MI)

