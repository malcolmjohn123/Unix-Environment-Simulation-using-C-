#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<unistd.h>
#include<dirent.h>


using namespace std;

// Case insensitive string comparison
bool caseInsensitiveStrCompare(string s1, string s2) {
   int i;
   for(i = 0; i < s1.size() && i <s2.size(); i++) {
       if (tolower(s1[i]) <tolower(s2[i])) return true;
       else if (tolower(s1[i]) >tolower(s2[i])) return false;
   }

   // s1 is smaller than s2
   if (i < s2.size()) {
       return true;
   }

   // s2 is smaller than s1
   else if (i < s1.size()) {
       return false;
   }

   return true;
}

int main() {
   cout<<"Welcome!\n";
   string command;
   while(1){
       // Showing current working directory
       char cwd[1024];
       getcwd(cwd, 1024);
       cout << cwd << ">";
      
       // Get the command from the user
       getline(cin, command);
       if (command.size() < 1)
	   		continue;
	   	
	   	//splitting string using spaces
	   	vector<string> words;
		istringstream iss(command);
		do{
			string subs;
        	iss >> subs;
        	words.push_back(subs);
    	} while (iss); 
	   	
	   	// mkdir
        if (words[0] == "mkdir") {
			// if nodirectory name mentioned
           	if (words.size() < 3) {
				cout<<"mkdir: missing operand\n";
            	continue;
            }

           // Printing error if fails
        	if(mkdir(words[1].c_str()) < 0) {
            	if (errno == EACCES) cout<<"mkdir failed Error " <<errno<<": Permissiondenied"<<endl;
            	else if (errno == EEXIST) cout<<"mkdir failed Error " <<errno<<": directory is alreadypresent"<<endl;
				}
        }
        
        // touch
        else if (words[0] == "touch"){
           // if nofilename mentioned
           if (words.size() < 3) {
              cout<<"mkdir: missing fileoperand\n";
              continue;
           }

           // create a file in append mode and close it
            ofstream ofs;
  			ofs.open (words[1].c_str(), ofstream::app);
  			ofs.close();
       }
       
        // cd
        else if (words[0] == "cd"){
           // if nodirectory mentioned
           if (words.size()< 3) {
              cout<<"cd: missing operand\n";
              continue;
           }

           // if cd fails
           if(chdir(words[1].c_str()) < 0) {
              cout<<"Invalid directory"<<words[1]<<endl;
           }
       }
       
        // ls
        else if (words[0] == "ls") {
        	// Set the directory for ls
        	string dir = cwd;
        	if (words.size()> 2) 
				dir = words[1];
          
        	// Check if the directory is present
        	DIR *dp =opendir(dir.c_str());;
        	if(dp == NULL){
            	cout<<"Invalid directory"<<dir<<endl;
            	continue;
           }

        	// Read while files are present and append to a vector
        	vector<string> filenames;
        	struct dirent *sd;
        	while ((sd=readdir(dp)) != NULL) {
            	// skip . and ..
            	if (sd->d_name[0] != '.')
					filenames.push_back(sd->d_name);
        	}

        	// Sort andprint the filenames
        	sort(filenames.begin(), filenames.end(),caseInsensitiveStrCompare);
        	for (int i = 0;i < filenames.size(); i++) {
            	cout<<filenames[i]<<endl;
        	}

        	// Close thedirectory
        	closedir(dp);
       }
       
        // exit
       	else if (words[0] == "exit"){
		   break;
       	}
       	
       	// Invalid command
       	else {
		   cout<<"Invalid command "<<words[0]<<endl;
        }
   }
   
   return 0;
}
       	


