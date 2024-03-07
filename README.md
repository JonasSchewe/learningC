# learningC

Welcome to the learningC repository. Here have I collected a few smaller tasks to give learners a deeper understanding of the C programming language. 

I've tried to design the tasks in such a way that each will focus on one specific topic such as file handling, string handling, networking, threads etc.

Additional task ideas are also always welcome. If you have one ready open an issue or create a pull request with a new task folder.

I hope you have fun doing these tasks. Good luck.

## Repository Structure

The repository ist structured as follows:
```
repository/
├─ taskname/
│  ├─ TASK.md
│  ├─ Makefile
│  ├─ implementation/
│  ├─ example/
│  ├─ tests/
├─ LICENSE
├─ .gitignore
├─ README.md
```
Each task has it's own subfolder. The folder is named the same as the task to quickly differentiate them. Each folder of a task shall contain the following:
-   TASK.md

    Complete description of the task itself, additional contraints and ressources such as man pages, advices, links or explanaitions. 

-   Makefile

    A Makefile to build the task and the example explanation. Additionally test are also great.

-   implementations/

    A folder for the implementation of the task by the learner. It can but needn't contain template files. The extent of assistance is to the discretion of the task designer.

-   example/

    A working and fully to spec example implementation of the descripted task to give an example solution for the learner.

-   tests/

    A folder for storing tests. It must be easy to run these test without complex installing of additional tools. Tools and libraries available in the package manager are okay. Please specify in the task description if and which additonal packages are needed to run these tests.
