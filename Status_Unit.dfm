object Status_Form: TStatus_Form
  Left = 282
  Top = 239
  BorderStyle = bsNone
  Caption = 'Status_Form'
  ClientHeight = 245
  ClientWidth = 391
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 392
    Height = 246
    BevelWidth = 3
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 24
      Top = 16
      Width = 353
      Height = 105
      Caption = 'Statistiques : '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Start_Time_Label: TLabel
        Left = 13
        Top = 22
        Width = 112
        Height = 13
        Caption = 'L'#39'houre de d'#233'marrage : '
      end
      object Elabsed_Time_Label: TLabel
        Left = 12
        Top = 46
        Width = 73
        Height = 13
        Caption = 'Temps '#233'coul'#233' :'
      end
      object End_Time_Label: TLabel
        Left = 14
        Top = 72
        Width = 73
        Height = 13
        Caption = 'L'#39'houre d'#39'arret :'
      end
    end
    object Panel2: TPanel
      Left = 24
      Top = 128
      Width = 353
      Height = 65
      BevelInner = bvLowered
      TabOrder = 1
      object Status_Label: TLabel
        Left = 23
        Top = 13
        Width = 100
        Height = 13
        Caption = 'op'#233'ration en cours....'
      end
      object ProgressBar1: TProgressBar
        Left = 8
        Top = 32
        Width = 337
        Height = 25
        Min = 0
        Max = 100
        TabOrder = 0
      end
    end
    object Close_Button: TButton
      Left = 139
      Top = 200
      Width = 142
      Height = 39
      Caption = '&Fermer'
      TabOrder = 2
      OnClick = Close_ButtonClick
    end
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 304
    Top = 80
  end
end
