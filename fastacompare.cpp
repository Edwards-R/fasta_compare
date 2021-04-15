#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

/*
 * Author: Rowan Edwards
 * Email: rowan.edw@gmail.com
 * 
 * This script loads in a FASTA file and compares the first two sequences it reads, returning the differences to the console as tsv
 * If characters start dropping and the otput is garbled, it's probably a \n\r error. Re-save your FASTA input under the operating
 * system that the code is running in.
 *
 * Run the script by compiling it, then passing the FASTA file as the first argument e.g.
 *
 *      g++ fastaread.cpp -o fastaread
 *      ./fastaread genomes.fasta
 *
 * Tested in Ubuntu 20.14
 *
*/

struct FASTA_Seq{
    std::string name;
    std::string seq;
};

std::vector<FASTA_Seq> ExtractSequences(char *arg){
    std::vector<FASTA_Seq> sequences; //Vector (aka C# list) to store the sequences in

    //Try and read the provided file
    std::ifstream input(arg);
    if(!input.good()){
        std::cerr << "Error opening '"<<arg<<"'. Bailing out." << std::endl;
        //Fail
        return sequences;
    }

    std::string line; //Storage for the line
    std::string comp="zoop"; //compiler
    
    FASTA_Seq sequence;

    while( std::getline( input, line )){ //While there is something to read
        if (line[0]=='>' || line.empty()){ //If line is a name OR blank

            //If there's something already in sequence, push it to the vector
            if(!sequence.name.empty()){
                sequences.push_back(sequence);
            }
            //Set up a new FASTA_Seq
            //Remove the '>' if present
            line.erase(std::remove(line.begin(), line.end(), '>'), line.end());
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            sequence.name=line;
            sequence.seq = ""; //resetting the sequence
        }
        else{

            line.erase(std::remove(line.begin(), line.end(), '\r'),line.end()); //Remove any \r
            sequence.seq+= line; //Remove the last character and append
        }
    }

    //Push the last one in
    sequences.push_back(sequence);

 
    return sequences;
}

void PrintSeqs(std::vector<FASTA_Seq> &sequences){
    for(FASTA_Seq seq : sequences){
        std::cout << "Name" << seq.name << std::endl;
        std::cout << "Sequence: " <<seq.seq << std::endl;
    }
}

void Compare(FASTA_Seq sequence1, FASTA_Seq sequence2){
    int maxLen;
    int startDif = -1;
    bool onStreak = false;

    std::vector<char> s1Diff;
    std::vector<char> s2Diff;

    std::string s1 = sequence1.seq;
    std::string s2 = sequence2.seq;

    if (s1.length()>s2.length()){
        maxLen = s2.length();
    }else{
        maxLen = s1.length();
    }



    for (int i=0; i<maxLen; i++){
        if(s1[i] != s2[i]){
            //start/continue streak
            if (onStreak==false){
                onStreak=true;
                startDif=i;
            }
            s1Diff.push_back(s1[i]);
            s2Diff.push_back(s2[i]);
        }else{
            if (onStreak){
                //dump streak info
                std::string s1string(s1Diff.begin(), s1Diff.end());
                std::string s2string(s2Diff.begin(), s2Diff.end());
                std::cout << "Start: " << (startDif+1) << "\tLength: " << (i-startDif) << "\t" << sequence1.name << ": " << s1string << "\t"<< sequence2.name << ": " << s2string << std::endl;

                //Reset
                onStreak=false;
                startDif=-1;

                s1Diff.clear();
                s2Diff.clear();
            }


        }
    }
}


int main( int argc, char **argv ){
    //Instructions on use
    if( argc <= 1 ){
        std::cerr << "Usage: "<<argv[0]<<" [in file]" << std::endl;
        return -1;
    }

    //Grab the sequences
    std::vector<FASTA_Seq> mySeq = ExtractSequences(argv[1]);

    //PrintSeqs(mySeq);

    Compare(mySeq[0], mySeq[1]);

    return 0;
}