# Developer Journal: CLISnakeGame

### Day 1 - Foundations and Failure
Started the project and laid down the basic structure:
- Drawing the board
- Initializing the board
- Snake position tracking  
  Everything was technically "built" but completely broken. Apples were cursed, snake logic was garbage, and memory leaks galore.

---

### Day 2 - Bug Spiral
Tried fixing the initial issues... ended up breaking things even further.  
Snake logic collapsed in on itself. Valgrind lit up like a Christmas tree. Zero visible progress.

---

### Day 3 - Total Breakdown
At this point the game either:
- Spawned a million apples for no reason
- Or had a snake made entirely of head  
  Nothing made sense. Morale: low. Faith in malloc: none.

---

### Day 4 - Overhaul & Completion
Complete logic rewrite from the ground up.  
Fixed the apple explosion bug (malloc was returning cursed memory), stabilized game behavior, and added:
- Proper snake growth
- Collision logic
- Cleanup routines  
  Project was finalized and fully documented.
