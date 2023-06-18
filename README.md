 The project is a system resembling a social network in which users can ask questions.
The questions can be of any kind, so the system supports different topics.
 The social network has several commands that can be used by any user during the use of the system. At the start of the program, the user should register in the system (via the command "signup") or enter the data of his already existing account (via the "login" command). Upon registration, each user should enter his first name, surname and password, after that the system generates a unique identification number for him. To log in an account, you only need to enter the first name and password and the system is looking for an existing user with such data.
After successfully logging on, each user can use the following commands:
1. "search" - Search for an existing topic by entered keyword.
2. "create" - Create a topic by submitted topic name and topic description. The system automatically generates a unique ID for each created topic and saved the name of the topic's creator.
3. "whoami" - Displays information about the user who is currently logged on.
4. "about<id>" - Displays information about the topic whose ID is entered.
5. "open<topic id>" / "open<full topic name>" - Opens a specific topic by submitted ID or full topic name. By opening a topic you are
    - "post" - Create a post in the opened topic
    - "p_open<id>" - Open a post by supplying the post's id.When a post is opened, the following commands can be used:
      
                                      1. "comment" - Comment about the opened topic.
      
                                      2. "comments" - See all the comments about the opened post.
      
                                      3. "upvote<id>"
      
                                      4. "downvote<id>"
      
                                      5. "p_close" -  Closing the opened post.
   
   - "quit" - Exit the opened topic.
   
6. "logout" - logout from the account.
7. "exit" - exit the network.