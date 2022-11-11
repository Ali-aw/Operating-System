# Operating-System
It is a distributed con-application developed with C language using process, pipes, signals, fork, etc...  consisting of 2 parts: a simple authentication protocol and a game between distributed clients.    The application is composed of the following components:  An authentication server (AuthServer) , Game Server (GameServer)  Distributed clients

# About
Message 1: for each round, the client contacts the server AuthServer by sending an authentication message. This message contains its username and password and respects the following format Auth:username:password If these information are correct, the AuthServer generates an access Ticket. This access ticket is a randomly generated integer by the server and serves to authenticate a client for one round only.

Message 2: The authentication server establishes a connection with the GameServer, and then sends the generated ticket to the authenticated user. This message respects the following format: Ticket:username:ticket Example: Ticket:Fadi:2398768 Upon receiving this message, the GameServer saves the username and the received ticket

Message 3: The GameServer replies by the message TicketSaved:username.

Message 4: The AuthServer sends to the client the authentication response. This response should respect the following format:<br />
   &nbsp;&nbsp;  • Ok:ticket (example: Ok:2398768 ) if the username and password matches the ones in his possession. <br />
  &nbsp;&nbsp;   • AuthenticationFailure in the case of an unsuccessful authentication<br />
     
     
Message 5: The client then sends to the Game server the received ticket. This message should respect the following format: Ticket:username:ticket 

Message 6: The GameServer verifies whether the received username and ticket correspond to the information saved on the server after receiving Message 2. The server sends then to the client the response which should respect the following format:<br />
 &nbsp;&nbsp;   •  InvalidAuthentication in the case where the ticket or the username are invalid<br />
  &nbsp;&nbsp;  •  WaitingPlayers in the case where the ticket and the username are valid but the number of connected clients having valid tickets is less than 3 <br />
   &nbsp;&nbsp; •  ReadyToStart in the case where the following two conditions are verified 1. The ticket and the username are valid, and 2. 3 clients having valid tickets are<br />            connected<br />
  &nbsp;&nbsp; • Noplace in the case where the number of clients having valid tickets is greater than 3. In this case, the concerned client can't participate in this round. <br />
   
   
# Features
Note that generated tickets are valid for a single round only, and a single player can play multiple rounds.  Once 3 clients are accepted, the Game server generates a Word (MysterWord) and then sends ReadyToStart for all Clients. The clients should predict this word they have 10 attempts.
Finding Near By Hospitals
Achievements & Rewards

# Advanced Functions
1- A client can ask the server to send him the list of connected players
2- Clients can chat
