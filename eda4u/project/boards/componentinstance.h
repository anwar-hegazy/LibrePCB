/*
 * EDA4U - Professional EDA for everyone!
 * Copyright (C) 2013 Urban Bruhin
 * http://eda4u.ubruhin.ch/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PROJECT_COMPONENTINSTANCE_H
#define PROJECT_COMPONENTINSTANCE_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include <eda4ucommon/units/all_length_units.h>
//#include <eda4ucommon/if_attributeprovider.h>
#include "../erc/if_ercmsgprovider.h"
#include <eda4ucommon/fileio/if_xmlserializableobject.h>

/*****************************************************************************************
 *  Forward Declarations
 ****************************************************************************************/

class GraphicsScene;

namespace project {
class Board;
class GenCompInstance;
class BI_Footprint;
}

namespace library {
class Component;
class Package;
}

/*****************************************************************************************
 *  Class ComponentInstance
 ****************************************************************************************/

namespace project {

/**
 * @brief The ComponentInstance class
 */
class ComponentInstance final : public QObject, /*public IF_AttributeProvider,*/
                                public IF_ErcMsgProvider, public IF_XmlSerializableObject
{
        Q_OBJECT
        DECLARE_ERC_MSG_CLASS_NAME(ComponentInstance)

        public:

            // Constructors / Destructor
            explicit ComponentInstance(Board& board, const XmlDomElement& domElement) throw (Exception);
            explicit ComponentInstance(Board& board, GenCompInstance& genCompInstance,
                                       const QUuid& componentUuid,
                                       const Point& position = Point(),
                                       const Angle& rotation = Angle()) throw (Exception);
            ~ComponentInstance() noexcept;

            // Getters
            Board& getBoard() const noexcept {return mBoard;}
            GenCompInstance& getGenCompInstance() const noexcept {return *mGenCompInstance;}
            const library::Component& getLibComponent() const noexcept {return *mComponent;}
            const library::Package& getLibPackage() const noexcept {return *mPackage;}

            // General Methods
            void addToBoard(GraphicsScene& scene) throw (Exception);
            void removeFromBoard(GraphicsScene& scene) throw (Exception);
            XmlDomElement* serializeToXmlDomElement() const throw (Exception);

            // Helper Methods
            //bool getAttributeValue(const QString& attrNS, const QString& attrKey,
            //                       bool passToParents, QString& value) const noexcept;


        signals:

            /// @copydoc IF_AttributeProvider#attributesChanged()
            void attributesChanged();


        private:

            // make some methods inaccessible...
            ComponentInstance();
            ComponentInstance(const ComponentInstance& other);
            ComponentInstance& operator=(const ComponentInstance& rhs);

            // Private Methods
            void initComponentAndPackage(const QUuid& componentUuid) throw (Exception);
            void init() throw (Exception);
            bool checkAttributesValidity() const noexcept;
            void updateErcMessages() noexcept;


            // General
            Board& mBoard;
            bool mAddedToBoard;
            GenCompInstance* mGenCompInstance;
            const library::Component* mComponent;
            const library::Package* mPackage;
            BI_Footprint* mFootprint;
};

} // namespace project

#endif // PROJECT_COMPONENTINSTANCE_H