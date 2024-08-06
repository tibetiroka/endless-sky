/* ShipInfoDisplay.h
Copyright (c) 2014 by Michael Zahniser

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

#include "ItemInfoDisplay.h"

#include <string>
#include <vector>

class Depreciation;
class PlayerInfo;
class Point;
class Ship;



// Class representing three panels of information about a given ship. One shows the
// ship's description, the second summarizes its attributes, and the third lists
// all outfits currently installed in the ship. This is used for the shipyard, for
// showing changes to your ship as you add upgrades, for scanning other ships, etc.
class ShipInfoDisplay : public ItemInfoDisplay {
public:
	ShipInfoDisplay() = default;
	ShipInfoDisplay(const Ship &ship, const PlayerInfo &player, bool descriptionCollapsed = true);

	// Call this every time the ship changes.
	void Update(const Ship &ship, const PlayerInfo &player, bool descriptionCollapsed = true,
		bool scrollingPanel = false);

	// Provided by ItemInfoDisplay:
	// int PanelWidth();
	virtual int AttributesHeight() const override;
	virtual int AttributesHeight(bool sale) const;

	// Provided by ItemInfoDisplay:
	// Point DrawDescription(const Point &topLeft) const;
	virtual Point DrawAttributes(const Point &topLeft) const override;
	virtual Point DrawAttributes(const Point &topLeft, const bool sale) const;
	Point DrawOutfits(const Point &topLeft) const;


private:
	void UpdateAttributes(const Ship &ship, const PlayerInfo &player, bool descriptionCollapsed, bool scrollingPanel);
	void UpdateOutfits(const Ship &ship, const PlayerInfo &player, const Depreciation &depreciation);
	void ResetEnergyHeatTable();


private:
	mutable FlexTable attributeHeader;
	mutable FlexTable energyHeatTable;
	mutable FlexTable outfits;
	mutable FlexTable sales;
};
