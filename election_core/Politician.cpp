#include "Politician.h"

int Politician::id() const { return id_; }

void Politician::setId(int id) { id_ = id; }

int Politician::constituencyId() const { return constituencyId_; }

void Politician::setConstituencyId(int id) { constituencyId_ = id; }

QString Politician::name() const { return name_; }

void Politician::setName(const QString& name) { name_ = name; }

QUrl Politician::imageUrl() const { return imageUrl_; }

void Politician::setImageUrl(const QUrl& imageUrl) { imageUrl_ = imageUrl; }

PartyDetails Politician::partyDetails() const { return partyDetails_; }

void Politician::setPartyDetails(const PartyDetails& partyDetails)
{
    partyDetails_ = partyDetails;
}

bool Politician::elected() const { return elected_; }

void Politician::setElected(bool elected) { elected_ = elected; }

bool Politician::candidate() const { return candidate_; }

void Politician::setCandidate(bool candidate) { candidate_ = candidate; }
