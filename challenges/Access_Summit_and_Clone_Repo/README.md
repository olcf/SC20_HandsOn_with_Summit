# Obtaining Access to Ascent and Clone Repository

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




When prompted for your PASSCODE, enter your PIN followed by the 6 digits shown on your token before pressing enter. For example, if your pin is <code>1234</code> and the 6 digits on the token are <code>000987</code>, enter <code>1234000987</code> when you are prompted for a PASSCODE.

> <strong>NOTE:</strong> The 6-digit code displayed on the SecurID token can only be used once. If prompted for multiple PASSCODE entries, always allow the 6-digit code to change between entries. Re-using the 6-digit code can cause your account to be automatically disabled.

Once you have successfully logged in to Summit, you can move on to Step 3.

## Step 3: Clone GitHub Repository for this Event

GitHub is a code-hosting platform for version control and collaboration. It lets you and others work together on projects from anywhere. For instance, we used GitHub to host, and track our changes to, the code for this event. Below, you will grab a copy of this GitHub repository to get access to the code.

### Clone the Repository

In order to continue with the other challenges, you will need to `clone` a copy of our repository. To do so, make sure you're in your "home" directory and issue the command:

```
$ cd /ccs/home/userid
$ git clone https://github.com/olcf/SC19_HandsOn_with_Summit.git
```

> NOTE: `git` itself is different than GitHub. It is a tool that developers install locally to manage version control and interact with remote code-hosting sites like GitHub.

This will add the code directory within your current directory. Now move into that directory:

```
$ cd SC19_HandsOn_with_Summit
```

Congratulations! You've completed your first challenge and can now move on to other challenges. Feel free to jump around to the ones you find most interesting.

<hr>
