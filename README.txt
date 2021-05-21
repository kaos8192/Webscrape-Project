Code by Geir Anderson for Project 1 in CMSC 318
Texts from https://sagadb.org

The goal of this program is to scan through English text translations of the Sagas from Iceland for mentions of honour or dishonour. (spelled with a u since the English texts are using an older, more formal style of British English)

It is to be noted that some texts have an alternate translation which will be scanned and that each Saga will take time to process, due to the scale of these prose narratives.

Used my code for the first programming homework cpp file in this course as a framework for this code


Compile:

compile process_data.cpp -o sagascan

Run:

./sagascan saga_texts/*

View Results:

cat saga_out.txt

*note* The output is mostly unlabled is formatted as the following

table:
file number | file name | word count | honor count | ratio of honor to total in percentage (they are all under 1%)

after table:
Full word count | Full honor count | Number of Sagas viewed
ratio of full honor to full word in percentage
average occurrence of honor
