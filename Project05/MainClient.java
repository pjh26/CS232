/**	MainClient.java defines the client side of the caesar cipher service
*
*	Student :	Peter Haagsma
* 	Date    :	May 7, 2019
*/

import java.net.*;
import java.io.*;

/** This class defines the caesar cipher client. It communicates with the caesar cipher server
*	as well as taking input from the console
*/
class CaesarCipherClient extends Object {
	private static Socket mySocket = null;
	private static BufferedReader input = null;
	private static PrintWriter output = null;
	private static BufferedReader stdIn = null;
	private static String HOST;
	private static int PORT;

	public CaesarCipherClient(String host, int port) {
		HOST = host;
		PORT = port;
		try {
			mySocket = new Socket(host, port);
			output = new PrintWriter(mySocket.getOutputStream(), true);
			input = new BufferedReader(new InputStreamReader(mySocket.getInputStream()));
			stdIn = new BufferedReader(new InputStreamReader(System.in));
		} catch (Exception e) {
			System.err.println(e);
		}
		System.out.println("Hail Caesar!\n\nWelcome to the Caesar Cipher Client! To begin, enter a number between 1 and 25.\n");
		System.out.println("Afterwards, enter the set of text that you would like to encode.\n");
		System.out.println("You can exit at any time by entering the command 'quit'.\n\nAnd don't forget, HAIL CAESAR!\n");
	}

	/** run()
	*	
	*	This function runs the loop that allows the user to input information and recieve info
	*	from the server. 
	*/
	public void run() {
		try {
			String userInput;
			while (true) {
				userInput = stdIn.readLine();
				if (userInput.equals("quit") == false) {
					output.println(userInput);
					System.out.println("echo: " + input.readLine());
				} else {
					break;
				}
			}
		} catch (UnknownHostException e) {
			System.err.println("Don't know about host " + HOST);
			System.exit(1);
		} catch (IOException e) {
			System.err.println("Couldn't get I/O for the connection to " + HOST);
			System.exit(1);
		}

		output.println("quit");
		
		try {
			input.close();
			output.close();
			mySocket.close();
			System.exit(0);
		} catch (Exception e) {
			System.err.println(e);
			System.exit(-1);
		}
	}

}

/** MainClient
*
*	This class contains a constructor that reads in arguments from the console to start the program
*/
public class MainClient {
	public static void main(String [] args) {
		if (args.length == 2) {
			CaesarCipherClient hailCaesar = new CaesarCipherClient(args[0], Integer.parseInt(args[1]));
			hailCaesar.run();
		} else {
			System.err.println("\nUsage: java CaesarCipherClient <host> <port>\n");
		}
	}
}