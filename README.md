I decided to use Boost Asio to handle the sockets. It seemed like a good choice when 
looking for libraries for sockets and I was already familiar with boost.

Using the async versions of the recv, send and write method, we are able to handle multiple
connections at the same time, letting asio handle the synchronization for us.

I left some debugging statements in the code to help figure out what is happening. I could 
have used a logging library, but felt it was a bit unecessary for the scope of this program.

## Prerequisites
Project was built using the following libraries and tools

* AppleClang 9.1.0.902003
* CMake 3.12.1
* Boost 1.68.0
* XCode 9.4.1
* Mac OS High Sierra (10.13.6)

## Improvements

* We could do more error verifications. For now, we simply check if there was an error, but in 
reality, we should have different behaviours based on error codes.
* It might be a good idea to move the response generation from the parser.
* We might generate an error code when the client sends an invalid command. We are returning "Invalid Command".
* The commands could come from a configuration file instead of hardcoding them in a static
object like we do in the Command class. This would be easier to change the format and add
new commands.
