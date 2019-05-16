#include "scorefile.hh"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

const std::string DEFAULT_FILENAME = "scores.txt";
const char SEP = ';';

// split function borrowed from past weeks of the course
// for the love of god start teaching a language that integrates split
std::vector<std::string> split(const std::string& s, const char delimiter, bool
                               ignore_empty){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and word.empty()))
        {
            result.push_back(word);
        }

    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

Scorefile::Scorefile()
{
    std::ifstream file(DEFAULT_FILENAME);
    if (!file.is_open()) {
        std::cout << DEFAULT_FILENAME << " can not be read, past scores can not"
                                         " be shown" << std::endl;
    }
    else {
        std::stringstream strStream;
        std::string std_contents = strStream.str();
        strStream << file.rdbuf();
        contents_ = QString::fromStdString(std_contents);
    }
}

QString Scorefile::get_contents()
{
    return contents_;
}

void Scorefile::write_score(std::string name, int score)
{
    // TODO: read file into objects
    std::ifstream read_file(DEFAULT_FILENAME);
    std::vector<Score> scores;
    // get all lines into a vector
    while (!read_file.eof()) {
        std::string read_line;
        getline(read_file, read_line);
        Score score = Score(read_line);
        scores.push_back(score);
    }


    // figure out where to place the new score
    auto correct_place = scores.begin();
    for (; correct_place != scores.end(); ++correct_place) {
        auto &saved_score = *correct_place;

        // when this score is worse than the new one, break
        if (saved_score.get_score() < score) {
            break;
        }
    }
    if (correct_place != scores.end()) {
        scores.insert(correct_place, Score(name, score));
        scores.pop_back();
    }


    std::ofstream write_file(DEFAULT_FILENAME);
    if (!write_file.is_open()) {
        std::cout << DEFAULT_FILENAME << " can not be written to, score will "
                                         "fail to save" << std::endl;
    }
    else {
        for (auto &score : scores) {
            write_file << score.serialize() << std::endl;
        }
    }
}


Scorefile::Score::Score(std::string name, int score)
{
    name_ = name;
    score_ = score;
}

Scorefile::Score::Score(std::string line)
{
    auto components = split(line, SEP, false);
    score_ = std::stoi(components.at(1));
    name_ = components.at(2);
}

std::string Scorefile::Score::serialize()
{
    std::stringstream stream;
    stream << score_;
    stream << SEP;
    stream << name_;
}

