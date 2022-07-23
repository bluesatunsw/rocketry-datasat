# rocketry-datasat
Cubesat-shaped data collection payload for Rocketry's Griffon rocket. Intended as a simple payload for the launch with the added benefit of being a helpful exercise for our satellite team. Deployment and recovery are not our problem.

## Specifications
- L3 M1590 motor.
- 1U cubesat formfactor (100mm\*100mm\*100mm).
- Practically unlimited weight limit.
- < 45 minutes waiting time on pad; system batteries must last this long at least.
- Max idle temperature on pad: 50 degrees.
- 4.74 seconds acceleration, at least that long decceleration, but probably longer. Up to 50G.
- Apogee (altitude ceiling): 3050 metres.


## Git Hygiene guide

For this project we will be using standard software engineering principles for our version control.

### Branches and forks

The most important of these is to **make sure to make a fresh pull request for every new feature**. If you want to work on the main repo, this also means a new branch for every feature. If you are using forks, you can branch as you please.

In this case a "feature" is any atomic piece of work you might be contributing, i.e. small enough that you are the only one likely to be working on it. For example, if you are working in /hardware you might implement the module to translate celestial coordinates to motor positions as a feature.

In the case that you are working on a bigger part with another person (or people) you can make a branch with sub-branches for each feature.

### Code review and pull requests

**Never commit directly to main**. The only exception to this is for making administrative changes like editing the readme, .gitignore, .codeowners and so on.
Whenever you finish a feature on a branch like described above, you should submit a **pull request** to get it merged back into a parent branch. Pull requests are also known as "merge requests" on GitLab and some other services (far clearer name frankly) because they basically give you a chance to write up what you've done and documents all the changes you are going to make. It also lets you safely specify how you are going to handle any conflicts between your branch and the parent.

Once you have made your pull request you should ideally get somebody else who didn't contribute to do a **code review** for you. This is mostly important on larger features or things where a lot can go wrong. While this project doesn't have critical stakes or a deployment to risk, it's a very important habit and will often catch a lot of mistakes that are very hard to find on your own (especially when they are errors in design rather than in code).
