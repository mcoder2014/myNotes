TEMPLATE = subdirs

SUBDIRS += \
    blocking_io \
    blocking_io_client \
    nonblocking_io_server \
    nonblocking_io_client \
    select_server \
    poll_server 

unix:!macx{
    SUBDIRS += \
        epoll_server
}
    