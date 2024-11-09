# -*- coding: utf-8 -*-

from odoo import models, fields, api, http
import re
import logging
import base64

_logger = logging.getLogger(__name__)


class LedMultiSync(models.Model):
    _name = "led.multisync"

    name = fields.Char(string="Site name")
    master_mac = fields.Char(string="Master's MAC", readonly=True)
    # slave_mac_list = fields.Char(string="Slave MAC list")
    node_list = fields.One2many(string="Device List", comodel_name="led.node", inverse_name="parent_id")
    text_list = fields.One2many(string="Text List", comodel_name="led.text", inverse_name="parent_id")
    display_text = fields.Char(string="Display Text")

    # is_pattern = fields.Boolean(string="Is Pattern?")
    is_pattern = fields.Boolean(string="Use Animation")

    should_update = fields.Boolean(string="Update Sync")

    animation_list = fields.One2many(comodel_name="led.animation", inverse_name="parent_id", string="Animation")

    def callback_button(self):
        pass


class Nodes(models.Model):
    _name = "led.node"

    mac = fields.Char(string="MAC Address")
    isMaster = fields.Boolean(string="Is Master?")
    parent_id = fields.Many2one(comodel_name="led.multisync", string="Led Controller")
    sequence = fields.Integer(string='Sequence', default=0)

    @api.model
    def create(self, vals):
        record = super(Nodes, self).create(vals)
        if record.isMaster:
            record._ensure_single_primary()
        return record

    def write(self, vals):
        res = super(Nodes, self).write(vals)
        if 'isMaster' in vals:
            for record in self:
                if record.isMaster:
                    record._ensure_single_primary()
        return res

    def _ensure_single_primary(self):
        if self.isMaster and self.parent_id:
            self.env['led.node'].search(
                [('parent_id', '=', self.parent_id.id), ('id', '!=', self.id), ('isMaster', '=', True)]
            ).write({'isMaster': False})


class TextField(models.Model):
    _name = "led.text"

    text = fields.Char(string="Text")
    parent_id = fields.Many2one(comodel_name="led.multisync")
    sequence = fields.Integer(string='Sequence', default=0)


class Animation(models.Model):
    _name = "led.animation"

    name = fields.Char(string="Animation")
    # custom_pattern = fields.Char(string="Custom Pattern")
    pattern_animation = fields.Selection(
        required="True",
        default="h_scroll",
        string="Pattern Animation",
        selection=[
            ('h_scroll', "Horizontal Scroll"),
            ('d_scroll_fold', "Diagonal Scroll-Fold"),
            ('d_scroll', "Diagonal Scroll"),
            ('wave', "Wave"),
            ('battery', "Battery"),
            ('h_scroll_text', "Horizontal Scrolling Text"),
        ],
    )

    sequence = fields.Integer(string='Sequence', default=0)

    parent_id = fields.Many2one(comodel_name="led.multisync")
