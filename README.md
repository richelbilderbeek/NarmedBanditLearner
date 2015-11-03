# NarmedBanditLearner

This C++ example code snippet shows how to implement a Learner class that has to optimize its
reward from an N-armed bandit. As one would expect, the Learner class knows nothing
about the N-Armed Bandit class' internals.

Give a Learner a set of actions, with every action having a certain expected reward.
Actions taken are evaluated by adjusting the expected rewards. The chance an
action is equal to its expected reward of the sum of expected rewards.

The Learner class has an internal Strategy Design Pattern, which enables the user to
select a different Learning Strategy at run-time. In the example main, this
Strategy is set randomly.
