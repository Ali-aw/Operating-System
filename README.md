# Operating-System
It is a distributed con-application developed with C language using process, pipes, signals, fork, etc...  consisting of 2 parts: a simple authentication protocol and a game between distributed clients.    The application is composed of the following components:  An authentication server (AuthServer) , Game Server (GameServer)  Distributed clients

# About
Message 1: for each round, the client contacts the server AuthServer by sending an authentication message. This message contains its username and password and respects the following format Auth:username:password If these information are correct, the AuthServer generates an access Ticket. This access ticket is a randomly generated integer by the server and serves to authenticate a client for one round only.

Message 2: The authentication server establishes a connection with the GameServer, and then sends the generated ticket to the authenticated user. This message respects the following format: Ticket:username:ticket Example: Ticket:Fadi:2398768 Upon receiving this message, the GameServer saves the username and the received ticket

Message 3: The GameServer replies by the message TicketSaved:username.

Message 4: The AuthServer sends to the client the authentication response. This response should respect the following format:
     • Ok:ticket (example: Ok:2398768 ) if the username and password matches the ones in his possession. 
     • AuthenticationFailure in the case of an unsuccessful authentication
     
# Features
Easy contact between blood donor and blood recipient through this android application.
Included:

User Databases
User Login & Sign up
Donor Details
Finding blood group easily
Finding Near By Hospitals
Achievements & Rewards
