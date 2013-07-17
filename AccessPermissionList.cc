#include "AccessPermissionList.h"

AccessPermissionList::AccessPermissionList()
{
    setAllPermissionsAsFalse() ;
}

AccessPermissionList::AccessPermissionList(std::string name,
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
    bool isAccountActive )
{
    this->name = name ;

    this->canViewResearchTopics = canViewResearchTopics ;
    this->canAddResearchTopics = canAddResearchTopics ;
    this->canRemoveResearchTopics = canRemoveResearchTopics ;
    this->canEditResearchTopics = canEditResearchTopics ;

    this->canViewParticipants = canViewParticipants ;
    this->canAddParticipants = canAddParticipants ;
    this->canRemoveParticipants = canRemoveParticipants ;
    this->canEditParticipants = canEditParticipants ;

    this->canViewQuestionnaires = canViewQuestionnaires ;
    this->canAddQuestionnaires = canAddQuestionnaires ;
    this->canRemoveQuestionnaires = canRemoveQuestionnaires ;
    this->canEditQuestionnaires = canEditQuestionnaires ;

    this->canViewUsers = canViewUsers ;
    this->canAddUsers = canAddUsers ;
    this->canRemoveUsers = canRemoveUsers ;
    this->canEditUsers = canEditUsers ;

    this->canViewSettings = canViewSettings ;
    this->canEditSettings = canEditSettings ;

    this->canSearchDatabase = canSearchDatabase ;
    this->canBackUp = canBackUp ;
    this->canCollaborate = canCollaborate ;
    this->canExport = canExport ;
    this->isAccountActive = isAccountActive ;
}

std::string AccessPermissionList::getName()
{
    return this->name ;
}

void AccessPermissionList::setName(std::string name)
{
    this->name = name ;
}

bool AccessPermissionList::getCanViewResearchTopics()
{
    return canViewResearchTopics ;
}

void AccessPermissionList::setCanViewResearchTopics(bool canViewResearchTopics)
{
    this->canViewResearchTopics = canViewResearchTopics ;
}

bool AccessPermissionList::getCanAddResearchTopics()
{
    return canAddResearchTopics ;
}

void AccessPermissionList::setCanAddResearchTopics(bool canAddResearchTopics)
{
    this->canAddResearchTopics = canAddResearchTopics ;
}

bool AccessPermissionList::getCanRemoveResearchTopics()
{
    return this->canRemoveResearchTopics ;
}

void AccessPermissionList::setCanRemoveResearchTopics(bool canRemoveResearchTopics)
{
    this->canRemoveResearchTopics = canRemoveResearchTopics ;
}

bool AccessPermissionList::getCanEditResearchTopics()
{
    return this->canEditResearchTopics ;
}

void AccessPermissionList::setCanEditResearchTopics(bool canEditResearchTopics)
{
    this->canEditResearchTopics = canEditResearchTopics ;
}

bool AccessPermissionList::getCanViewParticipants()
{
    return this->canViewParticipants ;
}

void AccessPermissionList::setCanViewParticipants(bool canViewParticipants)
{
    this->canViewParticipants = canViewParticipants ;
}

bool AccessPermissionList::getCanAddParticipants()
{
    return this->canAddParticipants ;
}

void AccessPermissionList::setCanAddParticipants(bool canAddParticipants)
{
    this->canAddParticipants = canAddParticipants ;
}

bool AccessPermissionList::getCanRemoveParticipants()
{
    return this->canRemoveParticipants ;
}

void AccessPermissionList::setCanRemoveParticipants(bool canRemoveParticipants)
{
    this->canRemoveParticipants = canRemoveParticipants ;
}

bool AccessPermissionList::getCanEditParticipants()
{
    return this->canEditParticipants ;
}

void AccessPermissionList::setCanEditParticipants(bool canEditParticipants)
{
    this->canEditParticipants = canEditParticipants ;
}

bool AccessPermissionList::getCanViewQuestionnaires()
{
    return this->canViewQuestionnaires ;
}

void AccessPermissionList::setCanViewQuestionnaires(bool canViewQuestionnaires)
{
    this->canViewQuestionnaires = canViewQuestionnaires ;
}

bool AccessPermissionList::getCanAddQuestionnaires()
{
    return this->canAddQuestionnaires ;
}

void AccessPermissionList::setCanAddQuestionnaires(bool canAddQuestionnaires)
{
    this->canAddQuestionnaires = canAddQuestionnaires ;
}

bool AccessPermissionList::getCanRemoveQuestionnaires()
{
    return canRemoveQuestionnaires ;
}

void AccessPermissionList::setCanRemoveQuestionnaires(bool canRemoveQuestionnaires)
{
    this->canRemoveQuestionnaires = canRemoveQuestionnaires ;
}

bool AccessPermissionList::getCanEditQuestionnaires()
{
    return canEditQuestionnaires ;
}

void AccessPermissionList::setCanEditQuestionnaires(bool canEditQuestionnaires)
{
    this->canEditQuestionnaires = canEditQuestionnaires ;
}

bool AccessPermissionList::getCanViewUsers()
{
    return canViewUsers ;
}

void AccessPermissionList::setCanViewUsers(bool canViewUsers)
{
    this->canViewUsers = canViewUsers ;
}

bool AccessPermissionList::getCanAddUsers()
{
    return this->canAddUsers ;
}

void AccessPermissionList::setCanAddUsers(bool canAddUsers)
{
    this->canAddUsers = canAddUsers ;
}

bool AccessPermissionList::getCanRemoveUsers()
{
    return this->canRemoveUsers ;
}

void AccessPermissionList::setCanRemoveUsers(bool canAddUsers)
{
    this->canRemoveUsers = canAddUsers ;
}

bool AccessPermissionList::getCanEditUsers()
{
    return this->canEditUsers ;
}

void AccessPermissionList::setCanEditUsers(bool canEditUsers)
{
    this->canEditUsers = canEditUsers ;
}

bool AccessPermissionList::getCanViewSettings()
{
    return this->canViewSettings ;
}

void AccessPermissionList::setCanViewSettings(bool canViewSettings)
{
    this->canViewSettings = canViewSettings ;
}

bool AccessPermissionList::getCanEditSettings()
{
    return this->canEditSettings ;
}

void AccessPermissionList::setCanEditSettings(bool canEditSettings)
{
    this->canEditSettings = canEditSettings ;
}

bool AccessPermissionList::getCanSearchDatabase()
{
    return this->canSearchDatabase ;
}

void AccessPermissionList::setCanSearchDatabase(bool canSearchDatabase)
{
    this->canSearchDatabase = canSearchDatabase ;
}

bool AccessPermissionList::getCanBackUp()
{
    return this->canBackUp ;
}

void AccessPermissionList::setCanBackUp(bool canBackUp)
{
    this->canBackUp = canBackUp ;
}

bool AccessPermissionList::getCanCollaborate()
{
    return this->canCollaborate ;
}

void AccessPermissionList::setCanCollaborate(bool canCollaborate)
{
    this->canCollaborate = canCollaborate ;
}

bool AccessPermissionList::getCanExport()
{
    return this->canExport ;
}

void AccessPermissionList::setCanExport(bool canExport)
{
    this->canExport = canExport ;
}

bool AccessPermissionList::getIsAccountActive()
{
    return this->isAccountActive ;
}

void AccessPermissionList::setIsAccountActive(bool isAccountActive)
{
    this->isAccountActive = isAccountActive ;
}

std::string AccessPermissionList::simpleSerialize()
{
    std::string serializedString ;

    if (this->canViewResearchTopics == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }

    if (this->canViewResearchTopics == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canAddResearchTopics == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canRemoveResearchTopics == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canEditResearchTopics == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }

    if (this->canViewParticipants == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canAddParticipants == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canRemoveParticipants == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canEditParticipants == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }

    if (this->canViewQuestionnaires == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canAddQuestionnaires == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canRemoveQuestionnaires == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canEditQuestionnaires == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }

    if (this->canViewUsers == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canAddUsers == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canRemoveUsers == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canEditUsers == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }

    if (this->canViewSettings == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canEditSettings == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }

    if (this->canSearchDatabase == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canBackUp == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canCollaborate == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->canExport == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }
    if (this->isAccountActive == true)
    {
        serializedString.append("1") ;
    }
    else
    {
        serializedString.append("0") ;
    }

    return serializedString ;
}

void AccessPermissionList::simpleDeserialize(std::string serializedAPL)
{
    /*
     *False by Default (From Initialization)
     */

    if (serializedAPL.at(0) == '1')
        {this->canViewResearchTopics = true ;}
    if (serializedAPL.at(1) == '1')
        {this->canAddResearchTopics = true ;}
    if (serializedAPL.at(2) == '1')
        {this->canRemoveResearchTopics = true ;}
    if (serializedAPL.at(3) == '1')
        {this->canEditResearchTopics = true ;}

    if (serializedAPL.at(4) == '1')
        {this->canViewParticipants = true ;}
    if (serializedAPL.at(5) == '1')
        {this->canAddParticipants = true ;}
    if (serializedAPL.at(6) == '1')
        {this->canRemoveParticipants = true ;}
    if (serializedAPL.at(7) == '1')
        {this->canEditParticipants = true ;}

    if (serializedAPL.at(8) == '1')
        {this->canViewQuestionnaires = true ;}
    if (serializedAPL.at(9) == '1')
        {this->canAddQuestionnaires = true ;}
    if (serializedAPL.at(10) == '1')
        {this->canRemoveQuestionnaires = true ;}
    if (serializedAPL.at(11) == '1')
        {this->canEditQuestionnaires = true ;}

    if (serializedAPL.at(12) == '1')
        {this->canViewUsers = true ;}
    if (serializedAPL.at(13) == '1')
        {this->canAddUsers = true ;}
    if (serializedAPL.at(14) == '1')
        {this->canRemoveUsers = true ;}
    if (serializedAPL.at(15) == '1')
        {this->canEditUsers = true ;}

    if (serializedAPL.at(16) == '1')
        {this->canViewSettings = true ;}
    if (serializedAPL.at(17) == '1')
        {this->canEditSettings = true ;}

    if (serializedAPL.at(18) == '1')
        {this->canSearchDatabase = true ;}
    if (serializedAPL.at(19) == '1')
        {this->canBackUp = true ;}
    if (serializedAPL.at(20) == '1')
        {this->canCollaborate = true ;}
    if (serializedAPL.at(21) == '1')
        {this->canExport = true ;}
    if (serializedAPL.at(22) == '1')
        {this->isAccountActive = true ;}
}

void AccessPermissionList::setAllPermissionsAsFalse()
{
    this->canViewResearchTopics = false ;
    this->canAddResearchTopics = false ;
    this->canRemoveResearchTopics = false ;
    this->canEditResearchTopics = false ;

    this->canViewParticipants = false ;
    this->canAddParticipants = false ;
    this->canRemoveParticipants = false ;
    this->canEditParticipants = false ;

    this->canViewQuestionnaires = false ;
    this->canAddQuestionnaires = false ;
    this->canRemoveQuestionnaires = false ;
    this->canEditQuestionnaires = false ;

    this->canViewUsers = false ;
    this->canAddUsers = false ;
    this->canRemoveUsers = false ;
    this->canEditUsers = false ;

    this->canViewSettings = false ;
    this->canEditSettings = false ;

    this->canSearchDatabase = false ;
    this->canBackUp = false ;
    this->canCollaborate = false ;
    this->canExport = false ;
    this->isAccountActive = false ;
}
