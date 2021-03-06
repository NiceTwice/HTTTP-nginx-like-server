//
// Created by Julien Karst on 05/01/2017.
//

#include "api/HttpResponse/HttpResponse.hh"

apouche::HttpResponse::~HttpResponse() {
  delete _header;
  delete _body;
}

apouche::StatusCode apouche::HttpResponse::getStatus() const {
    return _status;
}

void apouche::HttpResponse::setStatus(apouche::StatusCode status) {
    _status = status;
    if (_status == apouche::StatusCode::UndefinedStatusCode)
        _category = apouche::Category::Undefined;
    else if (_status <= apouche::StatusCode::SwitchingProtocols)
        _category = apouche::Category::Informational;
    else if (_status <= apouche::StatusCode::PartialContent)
        _category = apouche::Category::Success;
    else if (_status <= apouche::StatusCode::TemporaryRedirect)
        _category = apouche::Category::Redirection;
    else if (_status <= apouche::StatusCode::ExpectationFailed)
        _category = apouche::Category::ClientError;
    else
        _category = apouche::Category::ServerError;
}

apouche::Category apouche::HttpResponse::getCategory() const {
    return _category;
}

const std::string apouche::HttpResponse::getResponseLine() const {
    return std::to_string(_status) + " " + _message.at(_status);
}

apouche::IHttpHeader *apouche::HttpResponse::getHeaders() {
    return _header;
}

const apouche::IHttpHeader *apouche::HttpResponse::getHeaders() const {
    return _header;
}

void apouche::HttpResponse::setHeaders(IHttpHeader *header) {
    delete _header;
    _header = header;
}

apouche::IHttpBody *apouche::HttpResponse::getBody() {
    return _body;
}

const apouche::IHttpBody *apouche::HttpResponse::getBody() const {
    return _body;
}

void apouche::HttpResponse::setBody(IHttpBody *body) {
    delete _body;
    _body = body;
}

const std::string &apouche::HttpResponse::getVersion() const {
    return _version;
}

void apouche::HttpResponse::setVersion(const std::string &version) {
    _version = version;
}


apouche::HttpResponse::HttpResponse(apouche::IHttpHeader *header, apouche::IHttpBody *body, const std::string &version)
  : _header (header)
  , _body (body)
  , _version (version)
{
}

const std::string &apouche::HttpResponse::getStatusDescription() const {
     return _message.at(_status);
}

const std::map<apouche::StatusCode, std::string> apouche::HttpResponse::_message = {
  // Undefined
  {StatusCode::UndefinedStatusCode, "UndefinedStatusCode"},

  // Informational
  {StatusCode::Continue, "Continue"},
  {StatusCode::SwitchingProtocols, "SwitchingProtocols"},

  // Success
  {StatusCode::OK, "OK"},
  {StatusCode::Created, "Created"},
  {StatusCode::Accepted, "Accepted"},
  {StatusCode::NonAuthoritativeInformation, "NonAuthoritativeInformation"},
  {StatusCode::NoContent, "NoContent"},
  {StatusCode::ResetContent, "ResetContent"},
  {StatusCode::PartialContent, "PartialContent"},

  // Redirection
  {StatusCode::MultipleChoices, "MultipleChoices"},
  {StatusCode::MovedPermanently, "MovedPermanently"},
  {StatusCode::Found, "Found"},
  {StatusCode::SeeOther, "SeeOther"},
  {StatusCode::NotModified, "NotModified"},
  {StatusCode::UseProxy, "UseProxy"},
  {StatusCode::TemporaryRedirect, "TemporaryRedirect"},

  // ClientError
  {StatusCode::BadRequest, "BadRequest"},
  {StatusCode::Unauthorized, "Unauthorized"},
  {StatusCode::PaymentRequired, "PaymentRequired"},
  {StatusCode::Forbidden, "Forbidden"},
  {StatusCode::NotFound, "NotFound"},
  {StatusCode::MethodNotAllowed, "MethodNotAllowed"},
  {StatusCode::NotAcceptable, "NotAcceptable"},
  {StatusCode::ProxyAuthenticationRequired, "ProxyAuthenticationRequired"},
  {StatusCode::RequestTimeOut, "RequestTimeOut"},
  {StatusCode::Conflict, "Conflict"},
  {StatusCode::Gone, "Gone"},
  {StatusCode::LengthRequired, "LengthRequired"},
  {StatusCode::PreconditionFailed, "PreconditionFailed"},
  {StatusCode::RequestEntityTooLarge, "RequestEntityTooLarge"},
  {StatusCode::RequestURITooLarge, "RequestURITooLarge"},
  {StatusCode::UnsupportedMediaType, "UnsupportedMediaType"},
  {StatusCode::RequestedRangeNotSatisfiable, "RequestedRangeNotSatisfiable"},
  {StatusCode::ExpectationFailed, "ExpectationFailed"},

  // ServerError
  {StatusCode::InternalServerError, "InternalServerError"},
  {StatusCode::NotImplemented, "NotImplemented"},
  {StatusCode::BadGateway, "BadGateway"},
  {StatusCode::ServiceUnavailable, "ServiceUnavailable"},
  {StatusCode::GatewayTimeOut, "GatewayTimeOut"},
  {StatusCode::HTTPVersionNotSupported, "HTTPVersionNotSupported"},
};
