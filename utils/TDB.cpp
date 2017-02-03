#include <QtCore/QUrlQuery>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QDebug>
#include <QtCore/QTime>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QMessageBox>
#include <QtCore/QMetaEnum>
#include <auth/TAuth.h>
#include "auth/TDLogin.h"
#include "TDB.h"

TDBResponse TDB::request(QString path, QMap<QString, QString> params) {
	TDBResponse r;

	r.text = GET(path, params);
	r.code = getLastCode();
	r.time = getLastTime();

	return r;
}


QString TDB::GET(QString path, QMap<QString, QString> params) {
	QTime requestTime;
	requestTime.start();

	if (path.endsWith('/')) {
		path = path.remove(path.length() - 1, 1);
	}

	QNetworkRequest req;
	QNetworkReply *reply = nullptr;

	QString method = params.take("method");
	params.take("");

	QUrl c(path);
	QUrlQuery q;

	for (QString k : params.keys()) {
		if (k != "" && params[k] != "") {
			QString par = params[k];

			q.addQueryItem(k, par.startsWith("{{") ? getParameter(par) : par);
		}
	}

	if (method == "get") {
		c.setQuery(q);

		req.setUrl(c);
		reply = manager.get(req);

	} else if (method == "post") {
		req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

		req.setUrl(c);
		reply = manager.post(req, q.toString(QUrl::FullyEncoded).toUtf8());

	} else {
		return "";
	}

	QEventLoop wait;
	connect(&manager, SIGNAL(finished(QNetworkReply * )), &wait, SLOT(quit()));
	QTimer::singleShot(60000, &wait, SLOT(quit()));
	wait.exec();
	QByteArray rep = reply->readAll();
	reply->deleteLater();

	lastReply = QJsonDocument::fromJson(rep).object();
	lastCode = reply->error();
	lastTime = requestTime.elapsed();

	qDebug() << QString("[ %1] '%2'  params: '%3'")
			.arg(method.toUpper(), 4).arg(path.mid(path.indexOf('/', 8) + 1), 18).arg(params.keys().join(", "))
			.toStdString().c_str();

	return QString::fromUtf8(rep);
}

void TDB::checkAndRefreshToken() {
	GET("auth_api/check", {{"token", TConfig().getS("token")}});

	if (hasErrors()) {
		checkAndRefreshToken();

	}
}

bool TDB::hasErrors() {
	if (lastReply.contains("error")) {
		QString err = lastReply["error"].toString(), mess;
		qDebug() << "Error:" << err;

		if (err == "no_token" || err == "token_invalid") {
			TAuth::getToken();
		}

		return true;
	}

	return false;
}

QString TDB::getLastTime() {
	QString r = QString::number(lastTime);

	if (r.size() > 3) {
		r = r.insert(r.size() - 3, '\'');

	}

	return r + " ms";
}

QString TDB::getLastCode() {
	switch (lastCode) {
		case QNetworkReply::NoError:
			return "200 OK";
		case QNetworkReply::AuthenticationRequiredError:
			return "401 Auth required";
		case QNetworkReply::ContentNotFoundError:
			return "404 Not found";
		case QNetworkReply::ContentOperationNotPermittedError:
			return "403 || 405 Not permitted";
		case QNetworkReply::UnknownContentError:
			return "422 Validation error";
		case QNetworkReply::InternalServerError:
			return "500 Internal error";

		case QNetworkReply::ProxyAuthenticationRequiredError:
			return "407 ProxyAuthenticationRequired";
		case QNetworkReply::ContentConflictError:
			return "409 ContentConflict";
		case QNetworkReply::ContentGoneError:
			return "410 ContentGone";
		case QNetworkReply::ProtocolInvalidOperationError:
			return "400 ProtocolInvalidOperation";
		case QNetworkReply::OperationNotImplementedError:
			return "501 OperationNotImplemented";
		case QNetworkReply::ServiceUnavailableError:
			return "503 ServiceUnavailable";
		case QNetworkReply::UnknownServerError:
			return "502 .. 511";

		case QNetworkReply::HostNotFoundError:
			return "Error No host";
		case QNetworkReply::ConnectionRefusedError:
			return "Error ConnectionRefused";
		case QNetworkReply::RemoteHostClosedError:
			return "Error RemoteHostClosed";
		case QNetworkReply::TimeoutError:
			return "Error Timeout";
		case QNetworkReply::OperationCanceledError:
			return "Error OperationCanceled";
		case QNetworkReply::SslHandshakeFailedError:
			return "Error SslHandshakeFailed";
		case QNetworkReply::TemporaryNetworkFailureError:
			return "Error TemporaryNetworkFailure";
		case QNetworkReply::NetworkSessionFailedError:
			return "Error NetworkSessionFailed";
		case QNetworkReply::BackgroundRequestNotAllowedError:
			return "Error BackgroundRequestNotAllowed";
		case QNetworkReply::TooManyRedirectsError:
			return "Error TooManyRedirects";
		case QNetworkReply::InsecureRedirectError:
			return "Error InsecureRedirect";
		case QNetworkReply::UnknownNetworkError:
			return "Error UnknownNetwork";
		case QNetworkReply::ProxyConnectionRefusedError:
			return "Error ProxyConnectionRefused";
		case QNetworkReply::ProxyConnectionClosedError:
			return "Error ProxyConnectionClosed";
		case QNetworkReply::ProxyNotFoundError:
			return "Error ProxyNotFound";
		case QNetworkReply::ProxyTimeoutError:
			return "Error ProxyTimeout";
		case QNetworkReply::UnknownProxyError:
			return "Error UnknownProxy";
		case QNetworkReply::ContentAccessDenied:
			return "Error ContentAccessDenied";
		case QNetworkReply::ContentReSendError:
			return "Error ContentReSend";
		case QNetworkReply::ProtocolUnknownError:
			return "Error ProtocolUnknown";
		case QNetworkReply::ProtocolFailure:
			return "Error ProtocolFailure";

		default:
			return "Something else";
	}
}

QString TDB::getParameter(QString par) {
	par = par.mid(2, par.length() - 4);

	QJsonArray a = TConfig().get("vars").toArray();
	for (QJsonValue v : a) {
		QJsonObject o = v.toObject();

		if (o["name"].toString() == par)
			return o["str"].toString();
	}

	return "";
}


