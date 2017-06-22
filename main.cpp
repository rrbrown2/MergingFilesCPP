#if
/* 
Opens an ifstream file. read the file names on the ifstream file. open those files if they exist. then Counts the amount of words, characters, and punctuation on those files then merges the output.
it sounds more complicated than it is, i added as many comments as i could, hope it helps.
 */
#endif
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream file_reader;										// Object to read file
ofstream file_writer, output;										// Object to write file
string files_names[100];                                       // array can hold up to 100 different file names
string current_word, file_name;

int main() {
    output.open("write.txt");
	file_reader.open("merge_file_list.txt");						// Read file that contains files names
	int ix = 0;
	while (!(file_reader.eof())) {							// Looping on every word in the file
		file_reader >> file_name;							// Reading file name
		files_names[ix++] = file_name;					// Adding file name to list of names
	}

	// Merge all files
	file_writer.open("merged_file.txt");					// Open file to write in
	for(int i = 0; i < ix ; i++) {			// Looping on each file name
		file_name = files_names[i];							// Current file name
		ifstream fna(file_name.c_str());
		if (fna.good()) {									// Checking if file exists
			ifstream current_file_reader;					// Object to read file
			current_file_reader.open(file_name.c_str());			// Open current file name
			while (!(current_file_reader.eof())) {			// Looping through file contents
				current_file_reader >> current_word;		// Getting current word from file we are reading
				file_writer << current_word << " ";			// Writing to file
			}
			file_writer << endl;
		}
		else{
			output << " >> File " << file_name << " not available\n"; // if file to open does not exist
		}
  	}
	file_writer.close();									// Close file writer object to save
	//File stats
	int char_count = 0, punctuation_count = 0, word_count = 0, num_count  = 0;	// initialize variables to contain counts of types
	char current_char;
	int char_value;
	for(int i = 0 ; i < ix ; i++) {			// Looping on every file name
		file_name = files_names[i];							// Current file name
		ifstream fna(file_name.c_str());
		if (fna.good()) {									// Checking if file exists
			char_count = 0; 								// initialising values
			punctuation_count = 0;
			word_count = 0;
			num_count  = 0;

			ifstream current_file_reader;					// Creating object
			current_file_reader.open(file_name.c_str());			// Reading current file
			while(!current_file_reader.eof()) {				// Looping through file contents
				current_file_reader >> current_word;		// Getting current word
				word_count++;								// incremenating count of words
				for(int j = 0; j < current_word.length(); j++) {	// Looping through characters of current word
					current_char = current_word.at(j);		// Getting current character
					char_value = current_char;				// Getting ascii value of current character
					if ((65 <= char_value && char_value <= 90) || (97 <= char_value && char_value <= 122)) {
						// Checking if char is a letter using ascii values
						char_count++;						// Incrementing characters count
					} else {
						if (48 <= char_value && char_value <= 57) {
							//Checking if char is a number using ascii values
							num_count++;					// Incrementing numbers count
						} else {
							punctuation_count++;			// Incrementing punctuation count if not letter or number
						}
					}
				}
			}
			// Printing stats of file to the outputfile
			output << file_name << " word count is " << word_count << " words, ";
			output << char_count << " character count is ";
			output << " punctuation count is" << punctuation_count << endl;
		}
  	}

	return 0;
}
