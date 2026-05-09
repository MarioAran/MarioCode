#!/bin/bash
# --------------------------------------------------
# AWS Full Cleanup Script - DevOps Free Trial / Testing
# Borra instancias, volúmenes, EIPs, snapshots, AMIs, Lambdas y DynamoDB
# --------------------------------------------------
# 
# guardar en ~/scripts/
# alias aws-clean="bash ~/scripts/aws-cleanup.sh"
# 

echo "=== AWS Full Cleanup Script ==="
echo "Región: ${AWS_DEFAULT_REGION:-eu-west-1}"
echo

# 1️⃣ Terminar todas las instancias EC2
echo "[1/7] Terminando todas las instancias EC2..."
INSTANCE_IDS=$(aws ec2 describe-instances --query 'Reservations[*].Instances[*].InstanceId' --output text)

if [ -n "$INSTANCE_IDS" ]; then
    echo "Instancias encontradas: $INSTANCE_IDS"
    for id in $INSTANCE_IDS; do
        echo "Terminando instancia: $id"
        aws ec2 terminate-instances --instance-ids $id >/dev/null
    done
    echo "Solicitud de terminación enviada para todas las instancias."
else
    echo "No se encontraron instancias."
fi
echo

# 2️⃣ Eliminar volúmenes EBS disponibles
echo "[2/7] Borrando volúmenes EBS disponibles..."
VOLUME_IDS=$(aws ec2 describe-volumes --filters Name=status,Values=available --query 'Volumes[*].VolumeId' --output text)
if [ -n "$VOLUME_IDS" ]; then
    echo "Volúmenes disponibles: $VOLUME_IDS"
    for vol in $VOLUME_IDS; do
        echo "Eliminando volumen: $vol"
        aws ec2 delete-volume --volume-id $vol >/dev/null
    done
else
    echo "No hay volúmenes disponibles para borrar."
fi
echo

# 3️⃣ Liberar Elastic IPs sin asociar
echo "[3/7] Liberando Elastic IPs no asociadas..."
EIP_IDS=$(aws ec2 describe-addresses --query 'Addresses[?AssociationId==null].AllocationId' --output text)
if [ -n "$EIP_IDS" ]; then
    echo "Elastic IPs a liberar: $EIP_IDS"
    for eip in $EIP_IDS; do
        echo "Liberando Elastic IP: $eip"
        aws ec2 release-address --allocation-id $eip >/dev/null
    done
else
    echo "No hay Elastic IPs sin asociar."
fi
echo

# 4️⃣ Borrar snapshots creados por ti
echo "[4/7] Borrando snapshots propios..."
SNAPSHOT_IDS=$(aws ec2 describe-snapshots --owner-ids self --query 'Snapshots[*].SnapshotId' --output text)
if [ -n "$SNAPSHOT_IDS" ]; then
    echo "Snapshots a borrar: $SNAPSHOT_IDS"
    for snap in $SNAPSHOT_IDS; do
        echo "Eliminando snapshot: $snap"
        aws ec2 delete-snapshot --snapshot-id $snap >/dev/null
    done
else
    echo "No hay snapshots propios."
fi
echo

# 5️⃣ Deregistrar todas las AMIs propias
echo "[5/7] Deregistrando AMIs propias..."
AMI_IDS=$(aws ec2 describe-images --owners self --query 'Images[*].ImageId' --output text)
if [ -n "$AMI_IDS" ]; then
    echo "AMIs a deregistrar: $AMI_IDS"
    for ami in $AMI_IDS; do
        echo "Deregistrando AMI: $ami"
        aws ec2 deregister-image --image-id $ami >/dev/null
    done
else
    echo "No hay AMIs propias para deregistrar."
fi
echo

# 6️⃣ Borrar funciones Lambda (NUEVO)
echo "[6/7] Borrando funciones Lambda..."
LAMBDA_FUNCTIONS=$(aws lambda list-functions --query 'Functions[*].FunctionName' --output text)

if [ -n "$LAMBDA_FUNCTIONS" ]; then
    echo "Funciones Lambda encontradas: $LAMBDA_FUNCTIONS"
    for func in $LAMBDA_FUNCTIONS; do
        echo "Borrando Lambda: $func"
        aws lambda delete-function --function-name $func >/dev/null 2>&1
    done
else
    echo "No hay funciones Lambda para borrar."
fi
echo

# 7️⃣ Borrar tablas DynamoDB (NUEVO)
echo "[7/7] Borrando tablas DynamoDB..."
DYNAMODB_TABLES=$(aws dynamodb list-tables --query 'TableNames[*]' --output text)

if [ -n "$DYNAMODB_TABLES" ]; then
    echo "Tablas DynamoDB encontradas: $DYNAMODB_TABLES"
    for table in $DYNAMODB_TABLES; do
        echo "Borrando tabla: $table"
        aws dynamodb delete-table --table-name $table >/dev/null 2>&1
        # Pequeña pausa para que DynamoDB procese el borrado
        sleep 3
    done
else
    echo "No hay tablas DynamoDB para borrar."
fi
echo

echo "✅ Limpieza completa. Verifica en AWS Billing que no queden cargos."%