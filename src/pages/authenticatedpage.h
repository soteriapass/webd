#include "page.h"

class AuthenticatedPage : IPage
{
public:
    AuthenticatedPage();

    virtual void PreContent(std::stringstream& ss) override;
    virtual void HeaderContent(std::stringstream& ss) override;
    virtual void Page(std::stringstream& ss) override;

protected:
    bool GetIsAuthenticated() const             { return m_Authenticated; }
    void SetIsAuthenticated(bool authenticated) { m_Authenticated = authenticated; }

private:
    bool m_Authenticated;
};
