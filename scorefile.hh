#ifndef SCOREFILE_HH
#define SCOREFILE_HH
#include <QString>
#include <string>
#include <fstream>


class Scorefile
{
public:
    // reads
    Scorefile();
    // returns file contents
    QString get_contents();
    void write_score(std::string name, bool win, int time);

private:
    class Score {
    public:
        Score(std::string name, bool win, int time);
        // get from string
        Score(std::string line);

        std::string serialize();
    private:
        std::string name_;
        bool win_;
        int time_;
    };

    QString contents_;
};

#endif // SCOREFILE_HH
