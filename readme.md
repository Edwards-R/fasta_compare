#FASTA Compare CPP

**Author**: Rowan Edwards
**Email**: rowan.edw@gmail.com
**License**: [CC BY](https://creativecommons.org/licenses/by/4.0/)

This is a quick and dirty piece of code to read and compare two ***short*** FASTA sequences, outputting
the difference to the console as TSV

If the sequences are of uneven length it will run to the end of the shortest sequence

If the result comes back garbled with missing text/headers, it's likely a \r\n error
from cpp. Re-save your FASTA file under the same system that your script is running in.

Run the script by compiling it, then passing the FASTA file as the first argument e.g.

    g++ fastacompare.cpp -o fastacompare
    ./fastacompare genomes.fasta

Remember that this is only for SHORT sequences - it will fault out on sequences larger than a few mb!