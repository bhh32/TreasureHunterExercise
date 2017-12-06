#include "Message.h"
#include "Server.h"
#include "TreasureMap.h"
#include "Queue.h"
#include <iostream>

int main(int argc, char* argv[]) {

	const int numPlayers = 5;

	bool isFound = false;

	// Create a new sqaure TreasureMap that is 100 units wide and high
	TreasureMap map(50);

	// Create a new Server that will get the moves of the given number of players
	Server server(numPlayers);

	// Store the player positions, we'll up this as move messages come in
	Position playerPositions[numPlayers];

	// Create a message queue
	Queue<Message*> messageQueue;

	// Keep going until the treasure is found
	while (!isFound) 
	{

		// Get the first message
		Message* message = server.getNextMessage();

		// Process all the messages the server has for us
		while (message) 
		{

			std::cout << "Player " << message->getPlayerId() << " made move " << message->getMessageName() << std::endl;

			// Add messages to the queue
			messageQueue.Push(message);

			// Get the next message
			message = server.getNextMessage();
		}

		// TODO: Here, you should handled the first 5 messages in your queue (if you have that many)
		// move the player in the direction specified and test to see if they found the treasure.
		// If the treause is found print out the finder and exit.
		// Once you have handled the message, it will need to be deleted!

		for (int i = 0; i < 5 && !messageQueue.Empty(); ++i)
		{
			message = messageQueue.Pop();			
			//std::cout << "Pop #" << i + 1 << std::endl;
			switch (message->getMessageId())
			{
			case Message::eMessageId::TYPE_MOVE_STAY:
				break;
			case Message::eMessageId::TYPE_MOVE_NORTH:
				++playerPositions[message->getPlayerId()].y;
				break;
			case Message::eMessageId::TYPE_MOVE_SOUTH:
				--playerPositions[message->getPlayerId()].y;
				break;
			case Message::eMessageId::TYPE_MOVE_EAST:
				++playerPositions[message->getPlayerId()].x;
				break;
			case Message::eMessageId::TYPE_MOVE_WEST:
				--playerPositions[message->getPlayerId()].x;
				break;
			default:
				break;
			}

			
			if (map.isTreasurePos(playerPositions[i]))
			{
				std::cout << "Player " << message->getPlayerId() << " has found the treasure!";
				system("pause");
				isFound = true;
			}
		}

		std::cout << "End turn" << std::endl;
	}

	return 0;
}
