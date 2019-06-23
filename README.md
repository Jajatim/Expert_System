# Expert_System

42Lyon project "Expert System".


# Project state :
- Parser   0% (tests :   0%)
- Solver  75% (tests :  10%)


# Todo lists :
General todo list :
 - Figure out the logic of the program
 --- requesting something that is initially true, should you bother with the rules ?
 --- when a rules gives true and the other gives false, which one should you keep ?
 --- should the values be updated when requesting multiple answers or do every request start with the initial facts only ?
Parser todo list :
 - Everything needs to be done...
Solver todo list :
 - Make copies of rules before feeding them to the solver (or it'll write on them)
 - Make a copy of the initial fact array (it will update it while solving)
 - Make sure the rules fed to the solver are error free (it is not designed to handle wrong input)
 - Add the logic to handle "if and only if" statements
 - Can be greatly optimised if needed


# Bonus ideas :
Here are a few ideas that will probably not be so hard to implement :
 - Initial facts and requests can be requested directly from the prompt
 --- Could be the same with rules, but that might be a bit trickier to implement...
 - Verbose mode to print the solving process
 - Adding a list of random adjectives to replace the alphabet when printing the answer
 - "Percentage" mode which gives a percentage of how many facts are true when the request is finished
 - 8Ball mode which uses percentage mode to give a verbose answer (e.g. "It is very probable." or "Not a chance.")


# Presentation :
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

In this example, this gives the following solving process :
We need something that infers "green"
Rule #3 infers "green", and needs "frog".
Rule #1 infers "frog", and needs "croaks" and eats "flies".
(No more rules are needed as we already know both these facts, so we start solving it)
Fritz croaks and Fritz eats flies THEN Fritz is a frog
Fritz is a frog THEN Fritz is green

Hence we can safely say that our Fritz is green (also it is a frog, but apparently no one cares...).



(PS : Bisous à Shthevak)
