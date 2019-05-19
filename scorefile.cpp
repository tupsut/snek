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
        std::cout << DEFAULT_FILENAME << " can not be read or it might not exist"
                                         ", past scores can not be shown"
                  << std::endl;
    }
    else {
        std::stringstream strStream;
        std::string std_contents = strStream.str();
        strStream << file.rdbuf();
        contents_ = QString::fromStdString(std_contents);
    }
}

void Scorefile::write_score(std::string name, int points, int time)
{
    std::vector<Score> scores = get_scores();

    // figure out where to place the new score (find the first worse score)
    auto correct_place = scores.begin();
    for (; correct_place != scores.end(); ++correct_place) {
        auto &saved_score = *correct_place;

        if (saved_score.get_points() == points && saved_score.get_time() > time) {
            break;
        }

        // when this score is worse than the new one, and the time is worse, break
        if (saved_score.get_points() < points) {
            break;
        }
    }
    if (correct_place != scores.end()) {
        scores.insert(correct_place, Score(name, points, time));
        scores.pop_back();
    }


    std::ofstream write_file(DEFAULT_FILENAME);
    if (!write_file.is_open()) {
        std::cout << DEFAULT_FILENAME << " can not be written to, score will "
                                         "fail to save" << std::endl;
    }
    else {
        for (auto &score : scores) {
            write_file << score.to_string() << std::endl;
        }
    }
    write_file.close();
}

std::vector<Scorefile::Score> Scorefile::get_scores()
{
    // TODO: read file into objects
    std::ifstream read_file(DEFAULT_FILENAME);

    std::vector<Score> scores;

    // if exists
    if (read_file.is_open()) {
        // read 10 lines from file
        for (int i = 0; i != 10; ++i) {
            std::string read_line;
            getline(read_file, read_line);
            Score score = Score(read_line);
            scores.push_back(score);
        }
    }
    // if file doesn't exist, fill scores with 10 empty entries
    else {
        for (int i = 0; i != 10; ++i) {
            auto score = Score("nobody", 0, 0);
            scores.push_back(score);
        }
    }
    return scores;
}

QString Scorefile::pretty()
{
    std::vector<Score> scores = get_scores();

    QString text = "Position - Name - Points - Time\r\n";
    auto it = scores.begin();
    auto position = 1;
    for (; it != scores.end(); ++it) {
        text.append(
                    QString::fromStdString(std::to_string(position)) + " - " +
                    QString::fromStdString((*it).get_name()) + " - " +
                    QString::fromStdString(std::to_string((*it).get_points())) + " - " +
                    QString::fromStdString(std::to_string((*it).get_time())) +
                    QString("\r\n"));

        position +=1;
    }
    return text;
}

Scorefile::Score::Score(std::string name, int points, int time)
{
    name_ = name;
    points_ = points;
    time_ = time;
}

Scorefile::Score::Score(std::string line)
{
    auto components = split(line, SEP, false);
    points_ = std::stoi(components.at(0));
    time_ = std::stoi(components.at(1));
    name_ = components.at(2);
}

std::string Scorefile::Score::to_string()
{
    std::stringstream stream;
    stream << points_ << SEP << time_ << SEP << name_;
    return stream.str();
}

