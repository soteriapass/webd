#pragma once

#include <grpc++/grpc++.h>

#include <string>

class TokenAuthenticator : public grpc::MetadataCredentialsPlugin 
{
public:
    TokenAuthenticator(const std::string& token);

    grpc::Status GetMetadata(grpc::string_ref service_url, grpc::string_ref method_name, const grpc::AuthContext& channel_auth_context, std::multimap<grpc::string, grpc::string>* metadata) override;

    const std::string& GetToken() const { return m_Token; }
private:
    const std::string m_Token;
};
