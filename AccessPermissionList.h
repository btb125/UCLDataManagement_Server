#ifndef ACCESSPERMISSIONLIST_H
#define ACCESSPERMISSIONLIST_H

/*
 * Boost Serialization
 */
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

#include <string>

// Forward declaration of class boost::serialization::access
namespace boost
{
    namespace serialization
    {
        class access ;
    }
}

class AccessPermissionList
{
public:
    AccessPermissionList();
    AccessPermissionList(std::string name,
        bool canViewResearchTopics, bool canAddResearchTopics,
        bool canRemoveResearchTopics, bool canEditResearchTopics,
        bool canViewParticipants, bool canAddParticipants,
        bool canRemoveParticipants, bool canEditParticipants,
        bool canViewQuestionnaires,bool canAddQuestionnaires,
        bool canRemoveQuestionnaires, bool canEditQuestionnaires,
        bool canViewUsers, bool canAddUsers,
        bool canRemoveUsers,bool canEditUsers,
        bool canViewSettings,bool canEditSettings,
        bool canSearchDatabase,bool canBackUp,
        bool canCollaborate, bool canExport,
        bool isAccountActive ) ;

    std::string getName() ;
    void setName(std::string name) ;

    bool getCanViewResearchTopics() ;
    void setCanViewResearchTopics(bool canViewResearchTopics) ;
    bool getCanAddResearchTopics() ;
    void setCanAddResearchTopics(bool canAddResearchTopics) ;
    bool getCanRemoveResearchTopics() ;
    void setCanRemoveResearchTopics(bool canRemoveResearchTopics) ;
    bool getCanEditResearchTopics() ;
    void setCanEditResearchTopics(bool canEditResearchTopics) ;

    bool getCanViewParticipants() ;
    void setCanViewParticipants(bool canViewParticipants) ;
    bool getCanAddParticipants() ;
    void setCanAddParticipants(bool canAddParticipants) ;
    bool getCanRemoveParticipants() ;
    void setCanRemoveParticipants(bool canRemoveParticipants) ;
    bool getCanEditParticipants() ;
    void setCanEditParticipants(bool canEditParticipants) ;

    bool getCanViewQuestionnaires() ;
    void setCanViewQuestionnaires(bool canViewQuestionnaires) ;
    bool getCanAddQuestionnaires() ;
    void setCanAddQuestionnaires(bool canAddQuestionnaires) ;
    bool getCanRemoveQuestionnaires() ;
    void setCanRemoveQuestionnaires(bool canRemoveQuestionnaires) ;
    bool getCanEditQuestionnaires() ;
    void setCanEditQuestionnaires(bool canEditQuestionnaires) ;

    bool getCanViewUsers() ;
    void setCanViewUsers(bool canViewUsers) ;
    bool getCanAddUsers() ;
    void setCanAddUsers(bool canAddUsers) ;
    bool getCanRemoveUsers() ;
    void setCanRemoveUsers(bool canRemoveUsers) ;
    bool getCanEditUsers() ;
    void setCanEditUsers(bool canEditUsers) ;

    bool getCanViewSettings() ;
    void setCanViewSettings(bool canViewSettings) ;
    bool getCanEditSettings() ;
    void setCanEditSettings(bool canEditSettings) ;

    bool getCanSearchDatabase() ;
    void setCanSearchDatabase(bool canSearchDatabase) ;
    bool getCanBackUp() ;
    void setCanBackUp(bool canBackUp) ;
    bool getCanCollaborate() ;
    void setCanCollaborate(bool canCollaborate) ;
    bool getCanExport() ;
    void setCanExport(bool canExport) ;
    bool getIsAccountActive() ;
    void setIsAccountActive(bool isAccountActive) ;

    void setAllPermissionsAsFalse() ;

    std::string simpleSerialize() ;
    void simpleDeserialize(std::string serializedAPL) ;

    friend class boost::serialization::access ;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar
            & this->name
            & this->canViewResearchTopics
            & this->canAddResearchTopics
            & this->canRemoveResearchTopics
            & this->canEditResearchTopics

            & this->canViewParticipants
            & this->canAddParticipants
            & this->canRemoveParticipants
            & this->canEditParticipants

            & this->canViewQuestionnaires
            & this->canAddQuestionnaires
            & this->canRemoveQuestionnaires
            & this->canEditQuestionnaires

            & this->canViewUsers
            & this->canAddUsers
            & this->canRemoveUsers
            & this->canEditUsers

            & this->canViewSettings
            & this->canEditSettings

            & this->canSearchDatabase
            & this->canBackUp
            & this->canCollaborate
            & this->canExport
            & this->isAccountActive ;
    }

private:
    std::string name ;

    bool canViewResearchTopics ;
    bool canAddResearchTopics ;
    bool canRemoveResearchTopics ;
    bool canEditResearchTopics ;

    bool canViewParticipants ;
    bool canAddParticipants ;
    bool canRemoveParticipants ;
    bool canEditParticipants ;

    bool canViewQuestionnaires ;
    bool canAddQuestionnaires ;
    bool canRemoveQuestionnaires ;
    bool canEditQuestionnaires ;

    bool canViewUsers ;
    bool canAddUsers ;
    bool canRemoveUsers ;
    bool canEditUsers ;

    bool canViewSettings ;
    bool canEditSettings ;

    bool canSearchDatabase ;
    bool canBackUp ;
    bool canCollaborate ;
    bool canExport ;
    bool isAccountActive ;
};

#endif // ACCESSPERMISSIONLIST_H
