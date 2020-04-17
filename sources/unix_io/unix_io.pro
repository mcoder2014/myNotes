TEMPLATE = subdirs

SUBDIRS += \
    # 阻塞 io
    blocking_io_server \
    # 非阻塞 io 
    nonblocking_io_server \
    # 多路复用
    select_server \
    poll_server \
    # 异步 io
    aio_server \
    blocking_io_client 

unix:!macx{
    SUBDIRS += \
        epoll_server
}
    
