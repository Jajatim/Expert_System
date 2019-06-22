# Expert_System

42Lyon project "Expert System".

The aim of this project is to build an inference engine and solve requests via backward chaining.
Here is an example from wikipedia (source : https://en.wikipedia.org/wiki/Backward_chaining) :

Facts :
    Fritz croaks
    Fritz eats flies

Rules :
    1: If X croaks and X eats flies – Then X is a frog
    2: If X chirps and X sings – Then X is a canary
    3: If X is a frog – Then X is green
    4: If X is a canary – Then X is yellow
    
Request :
    Is Fritz green ?
    
The backward chaining works this way :
We find out which rules infer to our request, then get every parameter needed, and get which rules infer to their definition, and so on until every useful rule is known. We then work our way back to the request, solving each rule with the initial facts and moving on to the next level.

In this example, this gives the following :
We need something that infers "green"
Rule #3 infers "green", and needs "frog".
Rule #1 infers "frog", and needs "croaks" and eats "flies".
(No more rules are needed as we already know both these facts, so we start solving it)
Fritz croaks and Fritz eats flies THEN Fritz is a frog
Fritz is a frog THEN Fritz is green

Hence we can safely say that our Fritz is green (also it is a frog, but apparently no one cares...).


Project state :
- Parser   0% (tests : 0%)
- Solver  75% (tests : 0%)


(PS : Bisous à Shthevak)
