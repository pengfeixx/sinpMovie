// Copyright (C) 2020 ~ 2021, Deepin Technology Co., Ltd. <support@deepin.org>
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef _DMR_FFMPEG_PROBE
#define _DMR_FFMPEG_PROBE

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/hwcontext.h>
}

#include <QtCore>

#define RESULT_CONTINUE(n) {if(n) continue;}

namespace dmr {


    typedef int (*ffmAvHwdeviceCtxCreate)(AVBufferRef **device_ctx, enum AVHWDeviceType type,
                                           const char *device, AVDictionary *opts, int flags);

    typedef enum AVHWDeviceType (*ffmAvHwdeviceIterateTypes)(enum AVHWDeviceType prev);

    typedef const char* (*ffmAvHwdeviceGetTypeName)(enum AVHWDeviceType type);

    typedef int (*ffmAvformatOpenInput)(AVFormatContext **ps, const char *url, AVInputFormat *fmt, AVDictionary **options);

    typedef int (*ffmAvformatFindStreamInfo)(AVFormatContext *ic, AVDictionary **options);

    typedef AVCodec * (*ffmAvcodecFindDecoder)(enum AVCodecID id);

    typedef AVCodecParserContext *(*ffmAvParserInit)(int codec_id);

    typedef const AVCodecHWConfig *(*ffmAvcodecGetHwConfig)(const AVCodec *codec, int index);

    typedef AVCodecContext *(*ffmAvcodecAllocContext3)(const AVCodec *codec);

    typedef int (*ffmAvcodecParametersToContext)(AVCodecContext *codec, const AVCodecParameters *par);

    typedef void (*ffmAvformatCloseInput)(AVFormatContext **s);

    typedef int (*ffmAvcodecOpen2)(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options);

    typedef int (*ffmAvReadFrame)(AVFormatContext *s, AVPacket *pkt);

    typedef AVFrame *(*ffmAvFrameAlloc)(void);

    typedef int (*ffmAvcodecSendPacket)(AVCodecContext *avctx, const AVPacket *avpkt);

    typedef int (*ffmAvHwframeTransferData)(AVFrame *dst, const AVFrame *src, int flags);

    typedef int (*ffmAvImageGetBufferSize)(enum AVPixelFormat pix_fmt, int width, int height, int align);

    typedef void (*ffmAvFrameFree)(AVFrame **frame);

    typedef int (*ffmAvImageCopyToBuffer)(uint8_t *dst, int dst_size,
                                const uint8_t * const src_data[4], const int src_linesize[4],
                                enum AVPixelFormat pix_fmt, int width, int height, int align);

    typedef int (*ffmAvcodecReceiveFrame)(AVCodecContext *avctx, AVFrame *frame);

    typedef AVBufferRef *(*ffmAvBufferRef)(AVBufferRef *buf);

    typedef void *(*ffmAvMalloc)(size_t size);

    typedef void (*ffmAvcodecFreeContext)(AVCodecContext **avctx);

    typedef int (*ffmAvcodecClose)(AVCodecContext *avctx);

    typedef void (*ffmAvBufferUnref)(AVBufferRef **buf);

    /**
     * @file ??????????????????????????????
     */
    class HwdecProbe
    {
    public:
        /**
         * @brief ??????????????????
         * @return ????????????
         */
        static HwdecProbe& get();

        /**
         * @brief ???????????????????????????????????????
         * @param url ????????????
         * @param out hwList ???????????????????????????List
         * @return ?????????true,????????????false
         */
        bool isFileCanHwdec(const QUrl& url, QList<QString>& hwList);
    private:
        HwdecProbe();

        /**
         * @brief ???????????????
         */
        void initffmpegInterface();

        /**
         * @brief ???????????????
         * @param ctx ??????????????????
         * @param type ????????????
         * @return ??????0 ????????????0
         */
        int hwDecoderInit(AVCodecContext *ctx, int type);

        /**
         * @brief ???????????????????????????
         */
        void getHwTypes();

        /**
         * @brief ??????????????????????????????????????????
         * @param pDec ?????????
         * @param type ????????????
         * @return ???true ???false
         */
        bool isTypeHaveHwdec(const AVCodec *pDec, AVHWDeviceType type);

    private:
        //????????????
        static HwdecProbe             m_ffmpegProbe;
        //?????????????????????
        AVBufferRef                     *m_hwDeviceCtx;
        //??????????????????
        QList<AVHWDeviceType>           m_hwTypeList;
        // av_hwdevice_ctx_create ????????????
        ffmAvHwdeviceCtxCreate          m_avHwdeviceCtxCreate;
        // av_hwdevice_iterate_types ????????????
        ffmAvHwdeviceIterateTypes       m_avHwdeviceIterateTypes;
        //av_hwdevice_get_type_name ????????????
        ffmAvHwdeviceGetTypeName        m_avHwdeviceGetTypeName;
        // avformat_open_input ????????????
        ffmAvformatOpenInput            m_avformatOpenInput;
        // avformat_find_stream_info ????????????
        ffmAvformatFindStreamInfo       m_avformatFindStreamInfo;
        // avcodec_find_decoder ????????????
        ffmAvcodecFindDecoder           m_avcodecFindDecoder;
        // av_parser_init ????????????
        ffmAvParserInit                 m_avParserInit;
        // avcodec_get_hw_config ????????????
        ffmAvcodecGetHwConfig           m_avcodecGetHwConfig;
        // avcodec_alloc_context3 ????????????
        ffmAvcodecAllocContext3         m_avcodecAllocContext3;
        // avcodec_parameters_to_context ????????????
        ffmAvcodecParametersToContext   m_avcodecParametersToContext;
        // avformat_close_input ????????????
        ffmAvformatCloseInput           m_avformatCloseInput;
        // avcodec_open2 ????????????
        ffmAvcodecOpen2                 m_avcodecOpen2;
        // av_read_frame ????????????
        ffmAvReadFrame                  m_avReadFrame;
        // av_frame_alloc ????????????
        ffmAvFrameAlloc                 m_avFrameAlloc;
        // avcodec_send_packet ????????????
        ffmAvcodecSendPacket            m_avcodecSendPacket;
        // av_hwframe_transfer_data ????????????
        ffmAvHwframeTransferData        m_avHwframeTransferData;
        // av_image_get_buffer_size; ????????????
        ffmAvImageGetBufferSize         m_avImageGetBufferSize;
        // av_frame_free ????????????
        ffmAvFrameFree                  m_avFrameFree;
        // av_image_copy_to_buffer ????????????
        ffmAvImageCopyToBuffer          m_avImageCopyToBuffer;
        // m_avcodec_receive_frame; ????????????
        ffmAvcodecReceiveFrame          m_avcodecReceiveFrame;
        // v_buffer_ref ????????????
        ffmAvBufferRef                  m_avBufferRef;
        // av_malloc ????????????
        ffmAvMalloc                     m_avMalloc;
        // avcodec_free_context ????????????
        ffmAvcodecFreeContext           m_avcodecFreeContext;
        // avcodec_close ????????????
        ffmAvcodecClose                 m_avcodecClose;
        // av_buffer_unref ????????????
        ffmAvBufferUnref                m_avBufferUnref;
    };
}

#endif
