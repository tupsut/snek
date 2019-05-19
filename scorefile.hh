/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: snek: The Revengeance                                  #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: scorefile.hh                                               #
# Description: Declares a class implementing score files.          #
#                                                                  #
# Author: Saskia Simisker, 282598, saskia.simisker@tuni.fi         #
####################################################################
*/

#ifndef SCOREFILE_HH
#define SCOREFILE_HH
#include <QString>
#include <string>
#include <fstream>
#include <vector>

class Scorefile
{

public:

    /* \brief Reads a file and constructs the Scorefile item.
     */
    Scorefile();

    /* \brief Writes a new score into the file.
     *
     * \param[in] name Name of the player, taken from player input.
     * \param[in] score Points collected during the game.
     * \param[in] time Time taken to reach the score.
     */
    void write_score(std::string name, int points, int time);

    /* \brief Returns a printable version of the score list.
     */
    QString pretty();

private:

    /* \brief Class to represent individual scores.
     */
    class Score {

    public:
        /* \brief Creates a new Score.
         *
         * \param[in] name Name of the player, taken from player input.
         * \param[in] score Points collected during the game.
         * \param[in] time Time taken to reach the score.
         */
        Score(std::string name, int points, int time);

        /* \brief Creates a new Score based on a string representation.
         *
         * \param[in] line String contaning Score data.
         */
        Score(std::string line);

        /* \brief Creates a string representation based on a Score.
         */
        std::string to_string();

        /* \brief Returns the name associated with a score.
         */
        std::string get_name() {return name_;}

        /* \brief Returns the points in a score.
         */
        int get_points() {return points_;}

        /* \brief Returns the time in a score.
         */
        int get_time() {return time_;}

    private:
        std::string name_;  /**< Player name. */
        int points_;        /**< Points scored. */
        int time_;          /**< Time elapsed, in seconds. */
    };

    /* \brief Read scores from a file or create them/the file, if necessary.
     */
    std::vector<Score> get_scores();
};

#endif // SCOREFILE_HH
