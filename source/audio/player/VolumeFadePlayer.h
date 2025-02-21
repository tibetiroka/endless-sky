/* VolumeFadePlayer.h
Copyright (c) 2025 by tibetiroka

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

#include "AudioPlayer.h"

class VolumeFadePlayer : public AudioPlayer {
public:
	VolumeFadePlayer(SoundCategory category, std::unique_ptr<AudioSupplier> audioSupplier);

	void Update() override;

	void FadeOut();

private:
	static constexpr float VOLUME_DECREASE = 0.05;

	bool isFading = false;
};
