#include "process_data.hpp"

using namespace std;

/* Code by Geir Anderson
 * Texts from https://sagadb.org
 *
 * The goal of this program is to scan through English text translations of the Sagas from Iceland for mentions of honour or dishonour. (spelled with a u since the English texts are using an older, more formal style of British English)
 * It is to be noted that some texts have an alternate translation which will be scanned and that each Saga will take time to process, due to the scale of these prose narratives.
 *
 * Used my code for the first programming homework cpp file in this course as a framework for this code
 *
 * What must be done:
 * 1: read in text file(s)
 * 2: count total words per text and overall
 * 3: count honour
 * 4: calculate total words percentages of usage compared to a text total
 */


//Function for printing out results to terminal
void report_saga(map<string, int>& saga_mapo, map<string, int>& honour_mapo)
{
    /*
       for(auto& total_counts: saga_mapo)
       {
       cout << left << setw(20) << total_counts.first << "    |    " << total_counts.second << endl;
       }

       for(auto& honour_counts: honour_mapo)
       {
       cout << left << setw(20) << honour_counts.first << "    |    " << honour_counts.second << endl;
       }
       */

    ofstream saga_out;
    saga_out.open("saga_out.txt");

    int total_words = 0;
    int honour_words = 0;

    int track_me = 0;

    for(auto& s : saga_mapo)
    {
        for(int u = 0; u < 90; u++)
        {
            saga_out << "\u2500";
        }

        saga_out << endl;

        string name = s.first;

        size_t where_crop = name.rfind('/', name.length());
        if(where_crop != string::npos)
        {
            name = (name.substr(where_crop+1, name.length()-1));
        }
        auto h = honour_mapo.find(s.first);

        //if(honour_mapo.find(s.first) != honour_mapo.end())
        if(h != honour_mapo.end())
        {
            //auto& h = honour_mapo.find(s.first);
            float a = s.second;
            float b = h->second;
            float c = b / a;


            //cerr << a << endl;
            //cerr << b << endl;
            //cerr << c << endl;

            c = c * 100;

            //cerr << c << endl;

            total_words += a;

            honour_words += b;

            saga_out << left << setprecision(5)
                << setw(6) << track_me+1 << "   |   "
                << setw(32) << name << "   |   " 
                << setw(7) << s.second << "   |   " 
                << setw(6) << b << "   |   " 
                << setw(7) << c << endl;

            //cerr << ":D" << endl;
        }
        else
        {
            //cerr << "No words containing \"honour\" found." << endl;
            total_words += s.second;
            //cerr << "D:" << endl;
        }

        track_me++;

    }

    for(int u = 0; u < 90; u++)
    {
        saga_out << "\u2500";
    }

    saga_out << endl;

    saga_out << total_words << "    |     " << honour_words << "   |   " << track_me << endl;

    float tw = total_words;
    float hw = honour_words;
    float ratio = hw / tw;

    ratio = ratio * 100;

    saga_out << ratio << endl;

    saga_out << honour_words / track_me << endl;

    //cerr << ratio << endl;

    return;
}

//Function for finding words and applying to map
void calculate_sagas(ifstream& reading, map<string, int>& saga_mapi, map<string, int>& honour_mapsi, string file_current)
{
    string current_word = "";

    //cerr << file_current << endl;

    saga_mapi[file_current] = 0;

    while(reading >> current_word) //Read words from file and process
    {
        //cerr << current_word << "\t\t";

        for(auto itr = current_word.begin(); itr != current_word.end(); ) //Look for punctuation.
        {
            if(ispunct(*itr))
            {
                itr = current_word.erase(itr);
            }
            else
            {
                itr++;
            }
        }

        //cerr << current_word << endl;

        if(current_word.size() > 0)
        {
            transform(current_word.begin(), current_word.end(), current_word.begin(), ::tolower); //Make all char lowercase

            saga_mapi[file_current]++;

            size_t init = current_word.find("honour");
            if(init != string::npos)
            {
                //cerr << "@@@@@@ " << current_word << " @@@@@@" << endl;

                /*if(honour_mapsi.find(file_current) == honour_mapsi.end())
                  {*/
                if(honour_mapsi.find(current_word) == honour_mapsi.end())
                {
                    honour_mapsi[current_word] = 1; //Make new mapping if unique
                }

                else
                {
                    honour_mapsi[current_word]++; //Count up if not unique
                }
                /*}
                  else
                  {
                  }*/
            }
        }
    }

    cout << "\033[0m";
    return;
}

//Main opens file and connects to count
int main(int argc, char** argv)
{

    if(argc < 2)
    {
        cerr << "Input a text file, please." << endl;
        return -1;
    }

    string saga_read = "";
    ifstream toread;
    int i = 1;
    map<string, int> saga_map;
    map<string, int> honour_map;

    while(i < argc)
    {
        saga_read = argv[i];
        toread.open(saga_read);

        map<string, int> honour_saga_map;

        if(!toread.is_open()) //Make sure that file opens correctly
        {
            return -1;
        }

        calculate_sagas(toread, saga_map, honour_saga_map, saga_read);

        int a = 0;

        for(auto& grab_it : honour_saga_map)
        {
            a += grab_it.second;
        }

        if(a > 0)
        {
            honour_map[saga_read] = a;
        }

        i++;

        toread.close();
    }

    report_saga(saga_map, honour_map);

    //Ensure terminal format reset
    //cout << "\033[0m";

    return 0;
}
