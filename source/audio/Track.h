/* Track.h
Copyright (c) 2022 by RisingLeaf, Sam Gleske, tibetiroka

Endless Sky is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "../ConditionSet.h"
#include "../LocationFilter.h"
#include "../PlayerInfo.h"

#include <map>
#include <string>

class DataNode;



// Class to store a track of music that can be played
// when the correct conditions are present.
class Track {
public:
	Track() = default;

	// Construct and Load() at the same time.
	explicit Track(const DataNode &node);

	void Load(const DataNode &node);

	const std::string &Name() const;
	const std::string &Title() const;

	double GetVolumeModifier() const;
	int Wait() const;

	bool MatchesConditions(const PlayerInfo &player) const;


private:
	std::string name;
	double volumeModifier = 0.;
	// The name of the audio file
	std::string title;

	int wait = 0;

	ConditionSet toPlay;
	LocationFilter location;
};
