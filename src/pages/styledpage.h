#include "page.h"

class StyledPage : public IPage
{
public:
    virtual void PreContent(std::stringstream& ss) override;
    virtual void HeaderContent(std::stringstream& ss) override;
    virtual void Page(std::stringstream& ss) override;

protected:
   virtual void PreContentImpl(std::stringstream& ss)=0;
   virtual void HeaderContentImpl(std::stringstream& ss)=0;
   virtual void PageImpl(std::stringstream& ss)=0;
};
