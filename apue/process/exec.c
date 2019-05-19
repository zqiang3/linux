AMQP_URI:
- pyamqp://guest:guest@10.170.19.232:5672
- pyamqp://guest:guest@10.120.200.211:5672
- pyamqp://guest:guest@10.160.179.171:5672
WEB_SERVER_ADDRESS: 0.0.0.0:10000
max_workers: 30
SERVICE_CONTAINER_CLS: nameko_dyconf.ServiceContainer

DYCONF:
  enabled: true
  host: ms-consul-client.dockerv2.cc.163.com
  port: 8500

CONSUL:
  enabled: true
  host: ms-consul-client.dockerv2.cc.163.com
  port: 8500
  tags:
  - urlprefix-/v1/{service}
  - v1
  - docker.mobilegamelist
  - docker

STATSD:
  default:
    cluster: core
    host: statsd.cc.163.com
    port: 8125

ENV: production

SWAGGER:
  config:
    use_models: false
  resources:
    default:
      v1: spec/v1/api.yaml

ZIPKIN:
  writer: pyzipkin.logger_writer.LoggerWriter
  writer_kwargs: {}

CORS_ALLOW_ORIGIN_REGEXS:
  - ^https?://(\w+\.)?cc\.163\.com


LOGGING:
  disable_existing_loggers: false
  filters:
    tracefilter:
      (): pyzipkin.filters.TraceFilter
  formatters:
    accesslog:
      format: '%(message)s'
    bilog:
      format: '%(message)s'
    elk:
      format: '%(servicename)s:%(levelname)s %(asctime)s %(filename)s %(lineno)d %(traceid)s
        %(message)s'
    standard:
      format: '%(levelname)s %(asctime)s %(filename)s %(lineno)d %(traceid)s %(message)s'
  handlers:
    accesslog:
      class: logging.StreamHandler
      formatter: accesslog
    all:
      backupCount: 10
      class: logging.handlers.TimedRotatingFileHandler
      filename: logs/${SUPERVISOR_PROCESS_NAME:service}.log
      filters:
      - tracefilter
      formatter: standard
      when: midnight
    bilog:
      backupCount: 10
      class: logging.handlers.TimedRotatingFileHandler
      filename: logs/bi.log
      formatter: bilog
      level: INFO
      when: midnight
    console:
      class: logging.StreamHandler
      filters:
      - tracefilter
      formatter: standard
    tracing:
      backupCount: 10
      class: logging.handlers.TimedRotatingFileHandler
      filename: logs/tracing.log
      filters:
      - tracefilter
      formatter: accesslog
      when: midnight
  loggers:
    bilog:
      handlers:
      - bilog
      level: INFO
      propagate: false
    nameko.accesslog:
      handlers:
      - accesslog
    pyzipkin:
      handlers:
      - tracing
      level: INFO
    tracing:
      handlers:
      - tracing
      level: INFO
      propagate: 'false'
  root:
    handlers:
    - all
    level: INFO
  version: 1


REDIS_URIS:
  cache: redis-sentinel://10.170.46.33:26379,10.170.47.34:26379,10.170.48.34:26379/0?service_name=cc_ap_mobile8&prefer_master=true&socket_timeout=3

PYMONGO_URIS:
  mongo: mongodb://pt_app_online:pt_app_online@mongos-50031.cc.163.com:50031/cc_pt_app?connectTimeoutMS=10000&socketTimeoutMS=10000


WATCH_RECORD_URL: http://innerapi.cc.163.com/v1/watchrecord/watch_record
MGAMEPAGE_DATA_URL: http://api.cc.163.com/v1/mgamepage/game_page
GAME_FILTERS: http://innerapi.cc.163.com/v1/mgamepage/filters
GAME_HOT_REC: http://innerapi.cc.163.com/v1/mgamepage/hot_rec
MGAME_MATCH_URL: http://api.cc.163.com/v1/mgamematchact/query
MGAME_MATCH_BANNER_URL: http://api.cc.163.com/v1/mgamematchactbanner/query
RECOMMEND_ANCHOR_URL: http://api.cc.163.com/v1/freshanchor/recommend_anchor
MOBILENEWS_URL: http://api.cc.163.com/v1/mobilenews/config/
GAME_BANNER_URL: http://api.cc.163.com/v1/mobilebanner/get_banners
SHOW_LIST_URL: http://mactivity.cc.163.com/showbook/show_list
ALL_LIVE_LIST: http://api.cc.163.com/v1/mgameload/query_all_live
META_ANDROID_VERSION: 446725
META_IOS_VERSION: 2.9.4


https://195.154.241.91/h5ai/rtorrent/Fit18.Milena.Devi.Initial.Casting.XXX.1080p.MP4-YAPG/yp-f18mdic*、


http://mentedge.cc.163.com/entrank/anchor/current
http://mentedge.cc.163.com/entrank/user/current

http://mentedge.cc.163.com/entrank/anchor/pre
http://mentedge.cc.163.com/entrank/user/pre

http://mentedge.cc.163.com/entrank/anchor/preday


[1-9]\sGB|\d{2,2}.\d{1,}\sGB|\D[1-3]\d{2,3}.\d{1,}\sGB