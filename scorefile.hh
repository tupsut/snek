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
    void write_score(std::string name, int score);

private:
    class Score {
    public:
        Score(std::string name, int score);
        // get from string
        Score(std::string line);

        std::string serialize();
        int get_score() {return score_;}
    private:
        std::string name_;
        int score_;
    };

    QString contents_;
};

#endif // SCOREFILE_HH
