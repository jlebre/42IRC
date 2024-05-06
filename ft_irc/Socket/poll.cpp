#include "server.hpp"

void	Server::init_poll()
{
	_event.events = EPOLLIN | EPOLLOUT;
	_event.data.fd = _sock.fd;
	_events[0].data.fd = _sock.fd;

	event_fd = epoll_create1(0);

	epoll_ctl(event_fd, EPOLL_CTL_ADD, _sock.fd, &_event);

	memset(&_events, 0, sizeof(_events));
}
