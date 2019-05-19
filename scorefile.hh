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

        std::string get_name() {return name_;}

        /* \brief Returns the points in a score.
         *
         */
        int get_points() {return points_;}

        /* \brief Returns the time in a score.
         *
         */
        int get_time() {return time_;}

    private:
        std::string name_;  /**< Player name. */
        int points_;        /**< Points scored. */
        int time_;          /**< Time elapsed, in seconds. */
    };

    /* \brief Read scores from a file, or create them.
     */
    std::vector<Score> get_scores();

    QString contents_;      /**< Raw information from the score file. */
};

#endif // SCOREFILE_HH
