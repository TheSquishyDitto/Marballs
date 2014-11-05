/**
* A contact represents two bodies in contact. Resolving a
* contact removes their interpenetration, and applies sufficient
* impulse to keep them apart. Colliding bodies may also rebound.
* Contacts can be used to represent positional joints, by making
* the contact constraint keep the bodies in their correct
* orientation.
*/

#ifndef CONTACT_INCLUDED
#define CONTACT_INCLUDED

#include "engine_core.h"

namespace marballs
{

    class Contact
    {
        // Holds the position of the contact
        Vector3 contactPoint;

        // Holds the direction of the contact
        Vector3 contactNormal;

        /*
        * Holds the depth of penetration at the contact point. If both
        * bodies are specified then the contact point should be midway
        * between the inter-penetrating points.
        */
        marb penetration;
        
        /**
         * The contact resolver object needs access into the contacts to
         * set and effect the contact.
         */
        friend ContactResolver;
        
        protected:
            /**
             * A transform matrix that converts coordinates in the contact’s
             * frame of reference to world coordinates. The columns of this
             * matrix form an orthonormal set of vectors.
             */
            Matrix3 contactToWorld;
            /**
             * Holds the closing velocity at the point of contact. This is
             * set when the calculateInternals function is run.
             */
            Vector3 contactVelocity;
            /**
             * Holds the required change in velocity for this contact to be
             * resolved.
             */
            real desiredDeltaVelocity;
            /**
             * Holds the world space position of the contact point
             * relative to the center of each body. This is set when
             * the calculateInternals function is run.
             */
            Vector3 relativeContactPosition[2];
    };
    /**
     * The contact resolution routine. One resolver instance
     * can be shared for the whole simulation, as long as you need
     * roughly the same parameters each time (which is normal).
     */
    class ContactResolver
    {
        public:
         void ResolveContacts(Contact *contactArray, unsigned numContacts, real duration);
        
        protected:
            /**
             * Sets up contacts ready for processing. This makes sure their
             * internal data is configured correctly and the correct set of
             * bodies is made alive.
             */
            void PrepareContacts(Contact *contactArray, unsigned numContacts, real duration);
    };
         


}



#endif // CONTACT_INCLUDED
