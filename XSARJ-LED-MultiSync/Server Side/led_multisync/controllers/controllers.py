# -*- coding: utf-8 -*-
from odoo import api, fields, models, tools
from odoo import http
from odoo.http import request, Response, route, JsonRequest
from datetime import datetime, timedelta
import logging
import requests
import json

_logger = logging.getLogger(__name__)
from odoo.tools import date_utils


class CloudController(http.Controller):
    @http.route(
        ['/led/subscribe_master'],
        type="json",
        auth="public",
        methods=["POST"],
        website=False,
        cors='*',
        csrf=False,
    )
    def subscribe_master(self):
        data = json.loads(request.httprequest.data)
        mac_exists = http.request.env['led.multisync'].sudo().search([("master_mac", "=", data["master_mac"])])
        if not mac_exists:
            http.request.env["led.multisync"].sudo().create({"master_mac": data["master_mac"]})

        return {"status": "OK"}

    @http.route(
        ['/led/heartbeat'],
        type="json",
        auth="public",
        methods=["POST"],
        website=False,
        cors='*',
        csrf=False,
    )
    def check_update(self):
        data = json.loads(request.httprequest.data)
        master = http.request.env['led.multisync'].sudo().search([("master_mac", "=", data["master_mac"])])
        return {"should_update": master.should_update}

    @http.route(
        ['/led/get_action'],
        type="json",
        auth="public",
        methods=["POST"],
        website=False,
        cors='*',
        csrf=False,
    )
    def get_action(self):
        data = json.loads(request.httprequest.data)
        master = http.request.env['led.multisync'].sudo().search([("master_mac", "=", data["master_mac"])])
        master.should_update = False

        # nodes = master['node_list'].mapped("mac")

        ordered_nodes = master['node_list'].sorted(key=lambda r: (r.sequence, r.id)).mapped("mac")
        exclude_set = set([master.master_mac])
        filtered_macs = [mac for mac in ordered_nodes if mac not in exclude_set]
        ordered_texts = master['text_list'].sorted(key=lambda r: (r.sequence, r.id)).mapped("text")

        # animation = http.request.env['led.animation'].sudo().search([('id', "=", master['animation'].id)])

        animation_list = (
            master['animation_list'].sorted(key=lambda r: (r.sequence, r.id)).mapped("pattern_animation")
        )

        # custom_patterns = (
        #     master['animation_list'].sorted(key=lambda r: (r.sequence, r.id)).mapped("custom_pattern")
        # )

        # TODO
        return {
            "slave_mac_list": ",".join(list(filtered_macs)),
            "is_pattern": master.is_pattern,
            "display_text": ",".join(list(ordered_texts)),
            "animation_list": ",".join(list(animation_list)) if animation_list else False,
            # "custom_pattern": (",".join(list(custom_patterns))) if custom_patterns else False,
        }
        # return {
        #     "slave_mac_list": master.slave_mac_list,
        #     "is_pattern": master.is_pattern,
        #     "display_text": master.display_text,
        #     "pattern_animation": master.pattern_animation,
        #     "pattern": master.pattern,
        # }

    # def get_action(self):
    #     data = json.loads(request.httprequest.data)
    #     master = http.request.env['led.multisync'].sudo().search([("master_mac", "=", data["master_mac"])])
    #     master.should_update = False
    #     return {
    #         "slave_mac_list": master.slave_mac_list,
    #         "is_pattern": master.is_pattern,
    #         "display_text": master.display_text,
    #         "pattern_animation": master.pattern_animation,
    #         "pattern": master.pattern,
    #     }
