# Access Ascent and Clone Repository

Please follow the instructions below to login to OLCF's Ascent High Performance Computer(HPC) and grab a copy of the code we'll be using.


## Step 1: Use the username and password that you setup for Ascent to login. 

```
ssh username@login1.ascent.olcf.ornl.gov
```

If you did not obtain access to Ascent before the workshop, please follow [these instructions](https://docs.olcf.ornl.gov/systems/summit_user_guide.html#obtaining-access-to-ascent) to apply. However, we cannot guarantee that your access will be ready in time for you to do to the workshop. 


Once you have successfully logged in to Ascent, you can move on to Step 2.

## Step 2: Clone GitHub Repository for this Event

GitHub is a code-hosting platform for version control and collaboration. It lets you and others work together on projects from anywhere. For instance, we used GitHub to host, and track our changes to, the code for this event. Below, you will grab a copy of this GitHub repository to get access to the code.

### Clone the Repository

In order to continue with the other challenges, you will need to `clone` a copy of our repository. To do so, make sure you're in your "home" directory and issue the command:

```
$ cd /ccsopen/home/username
$ git clone https://github.com/olcf/SC20_HandsOn_with_Summit.git
```
You can do list, ls, to see the code directory within your current directory. 

```
[username@login1.ascent ~]$ ls
SC20_HandsOn_with_Summit
```

> NOTE: `git` itself is different than GitHub. It is a tool that developers install locally to manage version control and interact with remote code-hosting sites like GitHub.

Now move into that directory:

```
$ cd SC20_HandsOn_with_Summit
```

Congratulations! You've completed your first challenge and can now move on to other challenges. Feel free to jump around to the ones you find most interesting.

<hr>
